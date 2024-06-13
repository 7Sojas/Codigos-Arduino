const serialport = require('serialport'); // Módulo para comunicação serial
const express = require('express'); // Módulo para criar um servidor web
const mysql = require('mysql2'); // Módulo para conectar ao MySQL

// Constantes para configurações
// não altere!
const SERIAL_BAUD_RATE = 9600;
const SERVIDOR_PORTA = 3300;

// Habilita ou desabilita a inserção de dados no banco de dados
// false -> nao insere
// true -> insere
const HABILITAR_OPERACAO_INSERIR = true;

function gerarValoresFicticios(valorReal, quantidade, variacao) {
    const valores = [];
    for (let i = 0; i < quantidade; i++) {
        const variacaoAleatoria = Math.random() * (variacao * 2) - variacao;
        valores.push(valorReal + variacaoAleatoria);
    }
    return valores;
}   

// Função para comunicação serial
const serial = async (
    valoresDht11Umidade,
    valoresLm35Temperatura
) => {
    let poolBancoDados = ''

    // Conexão com o banco de dados MySQL
    poolBancoDados = mysql.createPool(
        {
            // altere!
            // Credenciais do banco de dados
            host: '10.18.34.28',
            user: 'aluno',
            password: 'Sptech#2024',
            database: 'sojas7',
            port: 3307
        }
    ).promise();

    // Lista as portas seriais disponíveis e procura pelo Arduino
    const portas = await serialport.SerialPort.list();
    const portaArduino = portas.find((porta) => porta.vendorId == 2341 && porta.productId == 43);
    if (!portaArduino) {
        throw new Error('O arduino não foi encontrado em nenhuma porta serial');
    }

    // Configura a porta serial com o baud rate especificado
    const arduino = new serialport.SerialPort(
        {
            path: portaArduino.path,
            baudRate: SERIAL_BAUD_RATE
        }
    );

    // Evento quando a porta serial é aberta
    arduino.on('open', () => {
        console.log(`A leitura do arduino foi iniciada na porta ${portaArduino.path} utilizando Baud Rate de ${SERIAL_BAUD_RATE}`);
    });

    // Processa os dados recebidos do Arduino
    arduino.pipe(new serialport.ReadlineParser({ delimiter: '\r\n' })).on('data', async (data) => {
        console.log(data);
        const valores = data.split(',');
        const lm35TemperaturaReal = parseFloat(valores[0]);
        const dht11UmidadeReal = parseFloat(valores[1]);

        // Gerar dados fictícios
        const lm35Temperaturas = gerarValoresFicticios(lm35TemperaturaReal, 28, 5);
        const dht11Umidades = gerarValoresFicticios(dht11UmidadeReal, 28, 5);

        // Armazena os valores dos sensores nos arrays correspondentes
        valoresLm35Temperatura.push(...lm35Temperaturas);
        valoresDht11Umidade.push(...dht11Umidades);

        // Insere os dados no banco de dados (se habilitado)
        if (HABILITAR_OPERACAO_INSERIR) {
            for (let contador = 0; contador < 28; contador++) {
                await poolBancoDados.execute(
                    'INSERT INTO leituraSensor (temperaturaLm, umidadeDht, fksensor) VALUES (ROUND(?), ROUND(?), ?)',
                    [lm35Temperaturas[contador], dht11Umidades[contador], `${contador + 1}`]
                );
                console.log("valores inseridos no banco: ", "TEMPERATURA:", lm35Temperaturas[contador] + ", UMIDADE: " + dht11Umidades[contador] + ", FKSENSOR: " + (contador + 1));
            }
        }
    });

    // Evento para lidar com erros na comunicação serial
    arduino.on('error', (mensagem) => {
        console.error(`Erro no arduino (Mensagem: ${mensagem}`)
    });
}

// não altere!
// Função para criar e configurar o servidor web
const servidor = (
    valoresDht11Umidade,
    valoresLm35Temperatura
) => {
    const app = express();

    // Configurações de CORS
    app.use((request, response, next) => {
        response.header('Access-Control-Allow-Origin', '*');
        response.header('Access-Control-Allow-Headers', 'Origin, Content-Type, Accept');
        next();
    });

    // Inicia o servidor na porta especificada
    app.listen(SERVIDOR_PORTA, () => {
        console.log(`API executada com sucesso na porta ${SERVIDOR_PORTA}`);
    });

    // Define os endpoints da API para cada tipo de sensor
    app.get('/sensores/dht11/umidade', (_, response) => {
        return response.json(valoresDht11Umidade);
    });
    app.get('/sensores/lm35/temperatura', (_, response) => {
        return response.json(valoresLm35Temperatura);
    });
}

// Função principal assíncrona para iniciar a comunicação serial e o servidor web
(async () => {
    // Arrays para armazenar os valores dos sensores
    const valoresDht11Umidade = [];
    const valoresLm35Temperatura = [];

    // Inicia a comunicação serial
    await serial(
        valoresDht11Umidade,
        valoresLm35Temperatura
    );

    // Inicia o servidor web
    servidor(
        valoresDht11Umidade,
        valoresLm35Temperatura
    );
})();
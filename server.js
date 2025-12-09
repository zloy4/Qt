const express = require('express');
const bodyParser = require('body-parser');
const multer = require('multer');
const path = require('path');
const { exec } = require('child_process');
const fs = require('fs');

const app = express();
const upload = multer({ dest: 'uploads/' });

// Создаём каталог uploads при старте
if (!fs.existsSync('uploads')) {
    fs.mkdirSync('uploads');
}

// Парсеры
app.use(bodyParser.urlencoded({ extended: false }));
app.use(express.static('public'));

// Главная страница
app.get('/', (req, res) => {
    res.send(`
        <h1>🔥 Vulnerable Web App</h1>
        <ul>
            <li><a href="/xss">XSS test</a></li>
            <li><a href="/rce">RCE test</a></li>
            <li><a href="/upload-form">File Upload (webshell)</a></li>
            <li><a href="/sqli?user=admin' OR '1'='1">SQLi demo</a></li>
        </ul>
    `);
});

///////////////////////////////
// 1) XSS
///////////////////////////////
app.get('/xss', (req, res) => {
    const value = req.query.q || "";
    res.send(`
        <h2>XSS тест</h2>
        <form method="GET">
            <input type="text" name="q" placeholder="Введите текст">
            <button type="submit">Send</button>
        </form>

        <p>Result: ${value}</p>
    `);
});

///////////////////////////////
// 2) RCE
///////////////////////////////
app.get('/rce', (req, res) => {
    res.send(`
        <h2>RCE тест (Remote Command Execution)</h2>
        <form method="GET" action="/exec">
            <input type="text" name="cmd" placeholder="Команда (id, ls, uname -a)">
            <button type="submit">Выполнить</button>
        </form>
    `);
});

app.get('/exec', (req, res) => {
    const cmd = req.query.cmd;

    if (!cmd) return res.send("Команда не указана");

    // Выполняем команду (очевидная уязвимость)
    exec(cmd, (err, stdout, stderr) => {
        res.send(`
            <h3>Команда: <code>${cmd}</code></h3>
            <pre>${stdout}${stderr}</pre>
        `);
    });
});

///////////////////////////////
// 3) File Upload
///////////////////////////////
app.get('/upload-form', (req, res) => {
    res.send(`
        <h2>Загрузка файла</h2>
        <form method="POST" enctype="multipart/form-data" action="/upload">
            <input type="file" name="file">
            <button type="submit">Upload</button>
        </form>
    `);
});

app.post('/upload', upload.single('file'), (req, res) => {
    res.send(`
        <h3>Файл загружен: ${req.file.originalname}</h3>
        <p>Сохранён как: ${req.file.path}</p>
    `);
});

///////////////////////////////
// 4) SQLi DEMO
///////////////////////////////
app.get('/sqli', (req, res) => {
    const user = req.query.user;
    res.send(`
        <h2>SQL Injection DEMO</h2>
        <p>Вы запросили пользователя: <code>${user}</code></p>

        <p><b>SQL запрос:</b></p>
        <pre>SELECT * FROM users WHERE username = '${user}'</pre>

        <p>Это всего лишь текст — БД нет.</p>
    `);
});

///////////////////////////////

app.listen(3000, () => {
    console.log("🔥 Vulnerable app running on port 3000");
});

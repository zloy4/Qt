const express = require('express');
const bodyParser = require('body-parser');
const multer = require('multer');
const path = require('path');
const { exec } = require('child_process');

const app = express();
const upload = multer({ dest: 'uploads/' });

app.use(bodyParser.urlencoded({ extended: false }));
app.use(express.static('public'));

// Уязвимость №1 — XSS
app.get('/xss', (req, res) => {
    const q = req.query.q || "";
    res.send(`<h1>XSS Test</h1><p>You searched: ${q}</p>`);
});

// Уязвимость №2 — RCE
app.get('/rce', (req, res) => {
    const cmd = req.query.cmd;
    if (!cmd) return res.send("No cmd given");
    exec(cmd, (err, stdout, stderr) => {
        res.send(`<pre>${stdout}${stderr}</pre>`);
    });
});

// Уязвимость №3 — File Upload + Webshell
app.post('/upload', upload.single('file'), (req, res) => {
    res.send("Uploaded: " + req.file.originalname);
});

// Главная
app.get('/', (req, res) => {
    res.send(`
        <h1>Vulnerable Test App</h1>
        <ul>
            <li><a href="/xss?q=<script>alert(1)</script>">XSS test</a></li>
            <li><a href="/rce?cmd=ls">RCE test</a></li>
            <li>Upload form (POST /upload)</li>
        </ul>
    `);
});

app.listen(3000, () => console.log('Vulnerable app running on port 3000'));

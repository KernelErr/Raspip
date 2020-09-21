const express = require('express')
const bodyParser = require('body-parser')
const { text } = require('body-parser')
const textParser = bodyParser.text()

const app = express()
const port = 3000

var messages = []
var messagesCount = 0
var resText

app.get('/', function (req, res) {
    resText = "<title>Raspip Server</title><h1>Welcome to Raspip Server!</h1></br>"
    if (messagesCount != 0) {
        resText += "<ul>"
        messages.forEach(buildList)
        resText += "</ul>"
    }
    res.send(resText)
})

function buildList(value) {
    resText += "<li>" + value + "</li>"
}

app.post('/', textParser, function (req, res) {
    if (messagesCount == 10) {
        for(var i=1;i<=9;i++){
            messages[i-1]=messages[i];
        }
        messagesCount=9;
    }
    messages[messagesCount] = req.ip + ' - ' + req.body
    console.log(messages[messagesCount])
    messagesCount++
    res.send('Gotcha')
})

app.listen(port, () => console.log(`Raspip server listening on port ${port}!`))
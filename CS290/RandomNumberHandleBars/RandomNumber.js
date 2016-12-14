var express = require('express');

var app = express();

app.set('port',3000);

app.get('/',function(req,res){
    res.type('text/plain');
    var number = Math.random();
    res.send('your number is '+number);
});

app.get('/other-page',function(req,res){
    res.type('text/plain');
    res.send('Bwahaha');    
});

app.use(function(req,res){
    res.type('text/plain');
    res.status(404);
    res.send('404-it\'s not here');
});

app.listen(app.get('port'),function(){
    console.log('we are running now');
});
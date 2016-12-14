//Travis Robinson
//CS290 Fall 2015
//Get and Post Request Assignment

var express = require('express');
var bodyParser = require('body-parser')
var handlebars = require('express-handlebars').create({defaultLayout:'main'});
var app = express();

app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

app.engine('handlebars', handlebars.engine);
app.set('view engine', 'handlebars');
app.set('port', 3456);


app.get('/',function(req,res){
    var data = [];
    for (var p in req.query)
    {
        data.push({'name':p,'value':req.query[p]})
    }
    var objectSentBack = {};
    objectSentBack.requestType = "GET";
    objectSentBack.list = data;
    res.render('home', objectSentBack);
});

app.post('/',function(req,res){
    var data = [];
    for (var p in req.query)
    {
        data.push({'name':p,'value':req.query[p]})
    }
    var objectSentBack = {};
    objectSentBack.requestType = "POST";
    objectSentBack.list = data;
    var dataBody = [];
    for (var p in req.body)
        {
            dataBody.push({'name':p,'value':req.body[p]})
        }
    objectSentBack.listBody = dataBody;
    res.render('home', objectSentBack);
});

app.use(function(req,res){
  res.status(404);
  res.render('404');
});

app.use(function(err, req, res, next){
  console.error(err.stack);
  res.type('plain/text');
  res.status(500);
  res.render('500');
});

app.listen(app.get('port'), function(){
  console.log('We\'re now running...');
});
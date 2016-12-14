var express = require('express');

var app = express();
var handlebars = require('express-handlebars').create({defaultLayout:'main'});

app.engine('handlebars', handlebars.engine);
app.set('view engine', 'handlebars');
app.set('port', 3000);

app.get('/testAPI',function(req,res){
  res.render('testingFaceBookAPI');
});

app.get('/gettingStarted',function(req,res){
  res.render('home');
});

app.get('/GettingAnAccessToken',function(req,res){
  res.render('gettingAnAccessToken');
});

function genContext(){
    var stuffToDisplay = {};
    stuffToDisplay.random = Math.random();
    return stuffToDisplay;
}

app.get('/random',function(req,res){
  res.render('randomNumber', genContext());
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
  console.log('Express started on http://localhost:' + app.get('port') + '; press Ctrl-C to terminate.');
});
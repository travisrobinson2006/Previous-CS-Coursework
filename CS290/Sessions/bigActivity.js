var currentTemp = 1000000;

var express = require('express');

var app = express();
var handlebars = require('express-handlebars').create({defaultLayout:'main'});
var session = require('express-session');
var bodyParser = require('body-parser');
var request = require('request');

app.use(bodyParser.urlencoded({ extended: false }));
app.use(session({secret:'SuperSecretPassword'}));

app.engine('handlebars', handlebars.engine);
app.set('view engine', 'handlebars');
app.set('port', 3000);

app.get('/',function(req,res,next){
   var context = {};
    if(!req.session.name)
    {
        res.render('newSession',context);
        return;
    }
    context.name = req.session.name;
    context.toDoCount = req.session.toDo.length || 0;
    context.toDo = req.session.toDo || [];
    console.log(context.toDo);
        
    request('http://api.openweathermap.org/data/2.5/weather?q='+context.toDo.city+',US&appid=dd98d581d382eeb25fd2a9abb9ceebf7',function(err,response,body){
        if(!err && response.statusCode < 400)
            {
                context.owm = body;
                //console.log("Successfully made request");
                //console.log(JSON.parse(body));
                //console.log(context.toDo.city);
            }
    });
    //console.log(context);    
    res.render('toDo',context);
});

app.post('/',function(req,res){
    var context = {};
    if (req.body['New List']){
        req.session.name = req.body.name;
        req.session.toDo = [];
        req.session.curId = 0;
    }
    
    if(!req.session.name)
    {
        res.render('newSession',context);
        return;
    }
    
    if(req.body['Add Item']){
        req.session.toDo.push({"name":req.body.name,"id":req.session.curId,"temp":req.body.temp,"city":req.body.city,"color":"black"});
        //console.log(req.session.toDo[req.session.curId].city);
        //req.session.toDo[req.session.curId].city = 'provo,ut';
        //console.log(req.session.toDo[req.session.curId].city);
        req.session.curId++;
    }
    
    for(var i = 0; i < req.session.curId; i++)
        {

//            console.log(req.session.toDo[i].temp);
//            console.log(req.session.toDo[i].city);
//            console.log(req.session.toDo[i].color);            
            //console.log(req.session.toDo[i].city);

                
            function getTemp(city){
                currentTemp = 0;
                console.log("First inside function"+currentTemp);
                request('http://api.openweathermap.org/data/2.5/weather?q='+city+',US&appid=dd98d581d382eeb25fd2a9abb9ceebf7',function(err,response,body){
                    if(!err && response.statusCode < 400)
                    {
                        var weather = JSON.parse(body);
                        currentTemp = weather.main.temp;
                        //currentTemp = 1000;
                        console.log("Inside function: "+currentTemp);
                        //return cityTemp;
                    }
                    //return "Error";
                });
                //currentTemp = 2500;
                console.log("Just before return "+currentTemp);
                return currentTemp;
            }
        var delay = 5000;
            setTimeout(function(){
                console.log("delayed");
            },delay);
            currentTemp = getTemp(req.session.toDo[i].city);
            console.log("Outside function "+currentTemp);
            if(req.session.toDo[i].temp < currentTemp)
                {
                    req.session.toDo[i].color = "red";
                }
            else
                {
                    req.session.toDo[i].color = "green";
                }
        }
    
    context.name = req.session.name;
    context.toDoCount = req.session.toDo.length;
    context.toDo = req.session.toDo;
    res.render('toDo',context);
    
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
  console.log('We are now running...');
});
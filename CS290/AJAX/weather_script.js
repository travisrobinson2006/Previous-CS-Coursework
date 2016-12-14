//Travis Robinson
//CS290
//AJAX Assignment
//Script for part 1
//Submitting and receivng ajax get request from openweather

/*var req = new XMLHttpRequest();
      req.open("GET", "http://api.openweathermap.org/data/2.5/weather?zip=97355,US&appid=dd98d581d382eeb25fd2a9abb9ceebf7", false);
      req.send(null);
      console.log(JSON.parse(req.responseText));*/

function submit()
{
    var zip = document.getElementById("zip_code").value
    var city = document.getElementById("city_state").value
    if(zip!=="")
        {
            var req = new XMLHttpRequest();
            req.open("GET", "http://api.openweathermap.org/data/2.5/weather?zip="+zip+",US&appid=dd98d581d382eeb25fd2a9abb9ceebf7", true);
            req.send(null);
            //console.log(JSON.parse(req.responseText));
        }
    else if(city!=="")
        {
            var req = new XMLHttpRequest();
            req.open("GET", "http://api.openweathermap.org/data/2.5/weather?q="+city+"&appid=dd98d581d382eeb25fd2a9abb9ceebf7", true);
            req.send(null);
            //console.log(JSON.parse(req.responseText)); 
        }
    else
        {
            console.log("error, no entries made");
        }
    req.addEventListener('load',function(){
        if(req.status>=200 && req.status<400){
            var response = JSON.parse(req.responseText)
            console.log(JSON.parse(req.responseText));

            var info = document.createElement("div");
            info.style.whiteSpace="pre";
            info.setAttribute("id","info");
            info.textContent += "City Name: "+response.name;
            info.textContent += "\n";
            info.textContent += "Temperature: "+response.main.temp;
            info.textContent += "\n";
            info.textContent += "Humidity: "+response.main.humidity;
            document.body.appendChild(info);            
        }
        else
        {
            console.log("Error: "+req.statusText)
        }
            
        
    });
    
    //var cityName = document.createElement("div");
    //cityName.setAttribute("id","cityName");
    //cityName.textContent = "City Name "+response.name;
    //document.body.appendChild(cityName);

    
    //var temperature = document.createElement("div");
    //temperature.setAttribute("id","temperature");
    //cityName.textContent = "Temperature: "+response.main.temp;
    //document.body.appendChild(temperature);
    
}

document.getElementById("submit").addEventListener("click",submit);
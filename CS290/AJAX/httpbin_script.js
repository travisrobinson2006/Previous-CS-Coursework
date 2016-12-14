//Travis Robinson
//CS290
//AJAX Assignment
//Script for part 2
//Submitting and receivng ajax post request from httpbin

function submit()
{
    var text = document.getElementById("data").value;
    if(text==="")
        {
            console.log("Error: No data present");
        }
    else
        {
            var req = new XMLHttpRequest();
            req.open("POST","http://httpbin.org/post",true);
            req.send(text);
        }
    req.addEventListener('load',function()
        {
            if(req.status>=200 && req.status<400){
            var response = JSON.parse(req.responseText)
            console.log(JSON.parse(req.responseText));
                
            var info = document.createElement("div");
            info.style.whiteSpace="pre";
            info.setAttribute("id","info");
            info.textContent = "You sent "+text+" and recieved "+response.data;
            document.body.appendChild(info); 
        }
    })
}



document.getElementById("submit2").addEventListener("click",submit);
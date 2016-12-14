console.log("Travis Robinson");
console.log("CS290");
console.log("Activity: JS Functions\n");

//call on functionWriter before it's called
functionWriter("before");

//declare functionWriter
function functionWriter(inputString)
{
    console.log("I am a function. I have the function keyword and can be called " + inputString + " I'm declared\n");
}

//call on functionWriter after it's called
functionWriter("after");


console.log("I'm about to crash because I'm calling on a function that is defined as a variable before it crashes");
//call on varWriter before it's declared
varWriter("before");

//declare varWriter
var varWriter = function(inputString)
{
    console.log("I am a function. I have the var keyword and can be called " + inputString + " I'm declared\n");
}

//call on varWriter after it's declared
varWriter("after");
/*
Travis Robinson
CS290
Assignment Higher-Order Functions and Objects
Due 10.26.2015
*/

function Automobile( year, make, model, type ){
    this.year = year; //integer (ex. 2001, 1995)
    this.make = make; //string (ex. Honda, Ford)
    this.model = model; //string (ex. Accord, Focus)
    this.type = type; //string (ex. Pickup, SUV)
}

var automobiles = [ 
    new Automobile(1995, "Honda", "Accord", "Sedan"),
    new Automobile(1990, "Ford", "F-150", "Pickup"),
    new Automobile(2000, "GMC", "Tahoe", "SUV"),
    new Automobile(2010, "Toyota", "Tacoma", "Pickup"),
    new Automobile(2005, "Lotus", "Elise", "Roadster"),
    new Automobile(2008, "Subaru", "Outback", "Wagon")
    ];

/*This function sorts arrays using an arbitrary comparator. You pass it a comparator and an array of objects appropriate for that comparator and it will return a new array which is sorted with the largest object in index 0 and the smallest in the last index*/

//Function for swapping elements of array
function swap(results,index,maxAuto)
{
    var temp = results[index];
    results[index] = results[maxAuto];
    results[maxAuto] = temp;
}

function sortArr( comparator, array ){
    /*your code here*/
    var results = array.slice();
    
    for (var iter = 0; iter < results.length-1; iter++)
        {
            var maxAuto = iter;
                for (var index = iter+1; index < array.length; index++)
                {
                    if (comparator(results[index],results[maxAuto]) === true)
                        {
                            maxAuto = index;
                        }
                }
                swap(results,iter,maxAuto);
        }
    return results;
}

/*A comparator takes two arguments and uses some algorithm to compare them. If the first argument is larger or greater than the 2nd it returns true, otherwise it returns false. Here is an example that works on integers*/
function exComparator( int1, int2){
    if (int1 > int2){
        return true;
    } else {
        return false;
    }
}

/*For all comparators if cars are 'tied' according to the comparison rules then the order of those 'tied' cars is not specified and either can come first*/

/*This compares two automobiles based on their year. Newer cars are "greater" than older cars.*/
function yearComparator( auto1, auto2){
    /* your code here*/
    if (auto1.year>auto2.year)
        {
            return true;
        }
    else
    {
        return false;
    }
}


/*This compares two automobiles based on their make. It should be case insensitive and makes which are alphabetically earlier in the alphabet are "greater" than ones that come later.*/
function makeComparator( auto1, auto2){
    /* your code here*/
    if (auto1.make<auto2.make)
        {
            return true;
        }
    else
        {
            return false;
        }
}


/*This compares two automobiles based on their type. The ordering from "greatest" to "least" is as follows: roadster, pickup, suv, wagon, (types not otherwise listed). It should be case insensitive. If two cars are of equal type then the newest one by model year should be considered "greater".*/
function typeComparator( auto1, auto2){
    /* your code here*/
    var a1Type = -10;
    var a2Type = -10;
    
    
    var autoType = ["wagon","suv","pickup","roadster"];
    
/*Commented out: can't use loops    
    for (var i = 0; i < autoType.length; i++)
        {
            if(auto1.type.toLowerCase() === autoType[i])
                {
                    a1Type = i;
                }
                
        }
    
        for (var i = 0; i < autoType.length; i++)
        {
            if(auto2.type.toLowerCase() === autoType[i])
                {
                    a2Type = i;
                }
                
        }
*/
//*****************Compare Auto1******************************       
    if (auto1.type.toLowerCase() === "roadster")
        {
            a1Type = 4;
        }
    else if (auto1.type.toLowerCase() === "pickup")
        {
            a1Type = 3;
        }
    else if (auto1.type.toLowerCase() === "suv")
        {
            a1Type = 2;
        }    
    else if (auto1.type.toLowerCase() === "wagon")
        {
            a1Type = 1;
        }    
//*****************Compare Auto2******************************    
    if (auto2.type.toLowerCase() === "roadster")
        {
            a2Type = 4;
        }
    else if (auto2.type.toLowerCase() === "pickup")
        {
            a2Type = 3;
        }
    else if (auto2.type.toLowerCase() === "suv")
        {
            a2Type = 2;
        }    
    else if (auto2.type.toLowerCase() === "wagon")
        {
            a2Type = 1;
        }        
    
    if (a1Type > a2Type)
        {
            return true;
        }
    else if (a1Type === a2Type)
        {
            if(yearComparator(auto1,auto2) === true)
                {
                    return true;
                }
            else
            {
                return false;    
            }
        }
    else
    {
        return false;    
    }
}


//logMe function writes automobiles to console-argument true prints all, including type
//argument false prints all except type
Automobile.prototype.logMe = function(bool)
{
    if (bool === true)
        {
            console.log(this.year + ' ' + this.make + ' ' + this.model + ' ' + this.type);
        }
    else if (bool === false)
        {
            console.log(this.year + ' ' + this.make + ' ' + this.model);    
        }
}



//print output
console.log("*****");
console.log("The cars sorted by year are:")
var results = sortArr(yearComparator,automobiles);
for (var index = 0; index < results.length; index++)
    {
        results[index].logMe(false);
    }
console.log("");
console.log("The cars sorted by make are:")
var results = sortArr(makeComparator,automobiles);
for (var index = 0; index < results.length; index++)
    {
        results[index].logMe(false);
    }
console.log("");
console.log("The cars sorted by type are:")
var results = sortArr(typeComparator,automobiles);
for (var index = 0; index < results.length; index++)
    {
        results[index].logMe(true);
    }

console.log("*****");

//console.log(typeComparator(automobiles[1],automobiles[3]));

/*Your program should output the following to the console.log, including the opening and closing 5 stars. All values in parenthesis should be replaced with appropriate values. Each line is a seperate call to console.log.

Each line representing a car should be produced via a logMe function. This function should be added to the Automobile class and accept a single boolean argument. If the argument is 'true' then it prints "year make model type" with the year, make, model and type being the values appropriate for the automobile. If the argument is 'false' then the type is ommited and just the "year make model" is logged.

*****
The cars sorted by year are:
(year make model of the 'greatest' car)
(...)
(year make model of the 'least' car)

The cars sorted by make are:
(year make model of the 'greatest' car)
(...)
(year make model of the 'least' car)

The cars sorted by type are:
(year make model type of the 'greatest' car)
(...)
(year make model type of the 'least' car)
*****

As an example of the content in the parenthesis:
1990 Ford F-150 */
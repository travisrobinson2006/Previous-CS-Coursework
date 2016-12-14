//Travis Robinson
//CS290
//deepComparison function


//vars used for testing
var obj1 = {a: 1, b: 2, c: 3};
var obj2 = {e: 1, f: 2, g: 3};
var obj3 = {a: 1, b: 2, c: 3, d: 4};
var obj4 = {a: 1, b: 5, c: 3};
var obj5 = null;
var obj6 = {a: 1, b: 3, c: 3};
var obj7 = {a: 1, b: 3, c: {e:5, f:99}}
var obj8 = {a: 1, b: 3, c: {e:5, f:99}}
var obj9 = {a: 1, b: 3, c: {e:5, f:9}}

//tests of deepComprison
console.log("Obj1 and Obj2: " + deepComparison(obj1,obj2));
console.log("Obj1 and Obj3: " + deepComparison(obj1,obj3));
console.log("Obj1 and Obj4: " + deepComparison(obj1,obj4));
console.log("Obj1 and Obj5: " + deepComparison(obj1,obj5));
console.log("Obj1 and Obj1: " + deepComparison(obj1,obj1));
console.log("Obj1 and Obj6: " + deepComparison(obj1,obj6));
console.log("Obj1 and Obj7: " + deepComparison(obj1,obj7));
console.log("Obj7 and Obj8: " + deepComparison(obj7,obj8));
console.log("Obj7 and Obj9: " + deepComparison(obj7,obj9));
console.log("1 and 1: " + deepComparison(1,1));
console.log("1 and 2: " + deepComparison(1,2));



function deepComparison(objA,objB)
{
    var counter = 0; //counter value used to ensure objects have same property values
    //both inputs are objects, both != null
    if (typeof(objA) == "object" && objA != null && typeof(objB) == "object" && objB != null)
    {
        //objects same length
        if(Object.keys(objA).length == Object.keys(objB).length)
        {
            //go through objects, make sure they have the same properties
            for (var prop1 in objA)
            {
                for (var prop2 in objB)
                {
                    if (prop1 == prop2)
                    {   
                        //if the property is the same, call on deepComparison to make sure they have the same value
                        //increment counter to make sure the number of same properties is the same as length
                        //that way we know they both have all the same properties
                        counter = counter+1;
                        if (deepComparison(objA[prop1],objB[prop2]) == false)
                        {
                            return false;
                        }
                    }
                }
            }
            //compare counter to length
            if (counter != Object.keys(objA).length)
            {
                return false;   
            }
        }
        else
        {
            return false;    
        }
    }
    //if not an object, compare values
    else
    {
        if (objA !== objB)
        {
            return false;   
        }
    }
    //return true if we haven't had to return false already
    return true;
}

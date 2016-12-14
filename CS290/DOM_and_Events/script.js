//Travis Robinson
//CS290
//Fall 2015
//DOM and Events Assignment

var horizontal = 1;
var vertical = 0;

var table = document.createElement("table");
document.body.appendChild(table);
table.setAttribute("id","table1");
table.style.border = "1px solid #000";

for (var index = 0;index<4;index++)
    {
        var addRow = document.createElement("tr");
        addRow.setAttribute("id","row"+index);
        document.getElementById("table1").appendChild(addRow);
    }

for (var index = 0; index<4;index++)
    {
        var addHead = document.createElement("th");
        var headerName = "Header "+(index+1);
        addHead.textContent = headerName;
        addHead.style.border = "1px solid #000";
        document.getElementById("row0").appendChild(addHead);
    }
for(var columns = 0;columns<4;columns++)
    {
        for (var rows = 1;rows<4;rows++)
            {
                var addCell = document.createElement("td");
                var cellName = (columns+1)+", "+rows;
                addCell.setAttribute("id","cell"+columns+rows);
                addCell.textContent = cellName;
                document.getElementById("row"+rows).appendChild(addCell);
                addCell.style.border = "1px solid #000";
            }
    }

var left = document.createElement("button");
left.setAttribute("id","leftButton");
left.textContent = "Left";
document.body.appendChild(left);

var right = document.createElement("button");
right.setAttribute("id","rightButton");
right.textContent = "Right";
document.body.appendChild(right);

var up = document.createElement("button");
up.setAttribute("id","upButton");
up.textContent = "Up";
document.body.appendChild(up);

var down = document.createElement("button");
down.setAttribute("id","downButton");
down.textContent = "Down";
document.body.appendChild(down);

var mark = document.createElement("button");
mark.setAttribute("id","marker");
mark.textContent = "Mark Cell";
document.body.appendChild(mark);

document.getElementById("cell"+vertical+horizontal).style.border = "3px solid #000"

function selectedCell(direction)
{
    document.getElementById("cell"+vertical+horizontal).style.border = "1px solid #000";
    
    if(direction === "right")
        {
            vertical++;
        }
    if(direction === "left")
        {
            vertical--;
            
        }
    if(direction === "up")
        {
            horizontal--;
            
        }
    if(direction === "down")
        {
            horizontal++;
            
        }
    
    document.getElementById("cell"+vertical+horizontal).style.border = "3px solid #000";
}

function moveLeft()
{
    if (vertical>0)
        {
            selectedCell("left");
        }
}

function moveRight()
{
    if(vertical < 3)
        {
            selectedCell("right");
        }
}

function moveUp()
{
    if (horizontal>1)
        {
            selectedCell("up");
        }
}

function moveDown()
{
    if(horizontal<3)
        {
            selectedCell("down");
        }
}

function markIt()
{
    document.getElementById("cell"+vertical+horizontal).style.backgroundColor = "yellow";
}

document.getElementById("leftButton").addEventListener("click",moveLeft);
document.getElementById("rightButton").addEventListener("click",moveRight);
document.getElementById("upButton").addEventListener("click",moveUp);
document.getElementById("downButton").addEventListener("click",moveDown);
document.getElementById("marker").addEventListener("click",markIt);
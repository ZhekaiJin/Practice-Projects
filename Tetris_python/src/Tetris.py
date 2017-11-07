#Author scott 
#class cs 102 
# final project tetris
from Tkinter import *
import random
def init(data):
    # set board dimensions and margin
    data.rows = 15
    data.cols = 10
    data.margin = 20
    # make board
    data.emptyColor = "blue"
    data.board = [([data.emptyColor] * data.cols) for row in range(data.rows)]
    iPiece = [[ True,  True,  True,  True]]  
    jPiece = [[ True, False, False ],[ True, True,  True]]
    lPiece = [[ False, False, True],[ True,  True,  True]] 
    oPiece = [[ True, True],[ True, True]]
    sPiece = [[ False, True, True],[ True,  True, False ]]  
    tPiece = [[ False, True, False ],[ True,  True, True] ]
    zPiece = [[ True,  True, False ],[ False, True, True]]
    tetrisPieces = [ iPiece, jPiece, lPiece, oPiece, sPiece, tPiece, zPiece ]
    data.tetrisPieces = tetrisPieces
    tetrisPieceColors = [ "red", "yellow", "magenta",
    "pink", "cyan", "green", "orange" ]
    data.tetrisPieceColors = tetrisPieceColors
    data.isGameOver = False
    data.pause = False
    newFallingPiece(data)
    data.score = 0

def newFallingPiece(data):
    data.newpiece = random.choice(data.tetrisPieces)
    data.newpiececolor = random.choice(data.tetrisPieceColors)
    data.fallrows = len(data.newpiece)
    data.fallcols = len(data.newpiece[0])
    data.fallrow = 0
    data.fallcol = data.cols//2-data.fallcols//2
    
    
# getCellBounds from grid-demo.py
def getCellBounds(row, col, data):
    # aka "modelToView"
    # returns (x0, y0, x1, y1) corners/bounding box of given cell in grid
    gridWidth  = data.width - 2*data.margin
    gridHeight = data.height - 2*data.margin
    x0 = data.margin + gridWidth * col / data.cols
    x1 = data.margin + gridWidth * (col+1) / data.cols
    y0 = data.margin + gridHeight * row / data.rows
    y1 = data.margin + gridHeight * (row+1) / data.rows
    return (x0, y0, x1, y1)

def moveFallingPiece(data,drow,dcol):
    data.fallcol += dcol
    data.fallrow += drow
    if not (fallingPieceIsLegal(data)):
        data.fallcol -=dcol
        data.fallrow -=drow
        return False
    return True


def fallingPieceIsLegal(data):

    for i in range (data.fallrows):
        for j in range (data.fallcols):
            if data.newpiece[i][j] == True:
                if  ((data.fallrow)<0 or (data.fallrow+data.fallrows)>data.rows) or (data.fallcol<0 or data.fallcol>(data.cols-data.fallcols)) or data.board[data.fallrow+i][data.fallcol+j]!=data.emptyColor:
                    return False
    return True

def rotateFallingPiece(data):
    fallpiece = data.newpiece
    fallrow = data.fallrow
    fallcol = data.fallcol
    fallrows = data.fallrows
    fallcols = data.fallcols
    newrow = fallcol
    newcol = fallrow
    newrows=fallcols
    newcols=fallrows
    oldcenterRow= fallrow+fallrows//2
    oldcenterCol = fallcol+fallcols//2
    newcenterRow = newrow + newrows//2
    newcenterCol = newcol + newcols//2
    data.fallrow = oldcenterRow - newrows//2
    data.fallcol = oldcenterCol - newcols//2
    data.newpiece = []
    for row in range(newrows): data.newpiece += [[False]*newcols]
    for row in range(fallrows):
        for col in range(fallcols):
            data.newpiece[fallcols-1-col][row] = fallpiece[row][col]
    
    data.fallrows = fallcols
    data.fallcols = fallrows 
    if not fallingPieceIsLegal(data):
        data.newpiece = fallpiece
        data.fallrows = fallrows
        data.fallcols = fallcols
        data.fallrow = fallrow
        data.fallcol = fallcol


def removeFullRows(data):
    counter = 0
    newRow = data.rows-1
    for i in range(data.rows):
        oldRow = data.rows-i-1
        rowisfull = True
        for cell in data.board[oldRow]:
            if cell == data.emptyColor:
                rowisfull = False
        if rowisfull == False:
            for i in range(data.cols):
                data.board[newRow][i] = data.board[oldRow][i]
            newRow-=1
        else:
            counter+=1
    for i in range(newRow):
        for j in range(data.cols):
            data.board[i][j] = data.emptyColor
    data.score += counter**2                
        




def mousePressed(event, data):
    pass

def keyPressed(event, data):
    if (event.keysym == "r"):
        init(data)
    if data.isGameOver== True:
        return
    if (event.keysym == "p"):
        data.pause = not data.pause
    if data.pause == True:
        return
    if (event.keysym == "c"):
        newFallingPiece(data)
    if (event.keysym == "Down"):
        moveFallingPiece(data,1,0)
    if (event.keysym == "Left"):
        moveFallingPiece(data,0,-1)
    if (event.keysym == "Right"):
        moveFallingPiece(data,0,1)
    if (event.keysym == "Up"):
        rotateFallingPiece(data)

        


def timerFired(data):
    if data.pause or data.isGameOver:
        return
    removeFullRows(data)
    if not moveFallingPiece(data,+1,0):
        placeFallingPiece(data)
        newFallingPiece(data)
        if not fallingPieceIsLegal(data):
            data.isGameOver = True
    data.timerDelay = 200
           
       
def placeFallingPiece(data):
    for i in range(data.fallrows):
        for j in range(data.fallcols):
            if data.newpiece[i][j] == True:
                data.board[data.fallrow+i][data.fallcol+j] = data.newpiececolor

def drawGame(canvas, data):
    canvas.create_rectangle(0, 0, data.width, data.height, fill="orange")
    drawBoard(canvas, data)
    canvas.create_text(200,10,text="score:%d"%data.score,font ="Arial 10 bold")
    if data.isGameOver == True:
        canvas.create_text(data.width/2,data.height/2,text ="Game Over",
            font="Arial 28 bold")

def drawBoard(canvas, data):
    # draw grid of cells
    for row in range(data.rows):
        for col in range(data.cols):
            drawCell(canvas, data, row, col,data.board[row][col])
    drawFallingPiece(canvas,data)

def drawCell(canvas, data, row, col,color):
    (x0, y0, x1, y1) = getCellBounds(row, col, data)
    m = 1 # cell outline margin
    canvas.create_rectangle(x0, y0, x1, y1, fill="black")
    canvas.create_rectangle(x0+m, y0+m, x1-m, y1-m, fill=color)
def drawFallingPiece(canvas,data):
    for i in range (data.fallrows):
        for j in range (data.fallcols):
            if data.newpiece[i][j] == True:
                drawCell(canvas,data,data.fallrow+i,data.fallcol+
                    j,data.newpiececolor)

def redrawAll(canvas, data):
    drawGame(canvas, data)

####################################
# use the run function （which is taken from online)
####################################

def run(width=300, height=300):
    def redrawAllWrapper(canvas, data):
        canvas.delete(ALL)
        redrawAll(canvas, data)
        canvas.update()    

    def mousePressedWrapper(event, canvas, data):
        mousePressed(event, data)
        redrawAllWrapper(canvas, data)

    def keyPressedWrapper(event, canvas, data):
        keyPressed(event, data)
        redrawAllWrapper(canvas, data)

    def timerFiredWrapper(canvas, data):
        timerFired(data)
        redrawAllWrapper(canvas, data)
        # pause, then call timerFired again
        canvas.after(data.timerDelay, timerFiredWrapper, canvas, data)
    # Set up data and call init
    class Struct(object): pass
    data = Struct()
    data.width = width
    data.height = height
    data.timerDelay = 100 # milliseconds
    init(data)
    # create the root and the canvas
    root = Tk()
    canvas = Canvas(root, width=data.width, height=data.height)
    canvas.pack()
    # set up events
    root.bind("<Button-1>", lambda event:
                            mousePressedWrapper(event, canvas, data))
    root.bind("<Key>", lambda event:
                            keyPressedWrapper(event, canvas, data))
    timerFiredWrapper(canvas, data)
    # and launch the app
    root.mainloop()  # blocks until window is closed
    print("game over!")

# run(300, 300)

####################################
# playTetris()  run 
####################################

def playTetris():
    rows = 20
    cols = 10
    margin = 20 # margin around grid
    cellSize = 20 # width and height of each cell
    width = 2*margin + cols*cellSize
    height = 2*margin + rows*cellSize
    run(width, height)

playTetris()

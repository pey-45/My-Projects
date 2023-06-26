import math
from tkinter import *

window = Tk()
window.title("Calculator")
window.geometry("204x260")
window.resizable(False, False)

# constants
button_width = 5
button_height = 2
button_padx = 2
button_pady = 2

# variables
i = 1
last_eq = False


# functions
def add(value):
    global i
    global last_eq

    if pantalla.get() == "0" or last_eq:
        pantalla.delete(0, END)
        i = 0
    pantalla.insert(i, value)
    last_op.insert(len(last_op.get()), value)
    i += 1
    last_eq = False


def op(value):
    global i
    global last_eq

    if 'u' in pantalla.get():
        pantalla.delete(0, END)
        pantalla.insert(0, "0")
    pantalla.insert(i, value)
    last_op.delete(0, END)
    last_op.insert(0, value)
    i += 1
    last_eq = False


def action_c():
    global i
    global last_eq

    pantalla.delete(0, END)
    add(0)
    i = 1
    last_eq = False


def action_equals():
    global i
    global last_eq

    if 'u' in pantalla.get():
        pantalla.delete(0, END)
        pantalla.insert(0, "0")
    if last_eq:
        pantalla.insert(i, last_op.get())
    n = float(eval(pantalla.get()))
    pantalla.delete(0, END)
    if n > math.pow(10, 19):
        pantalla.insert(0, "Number is too large")
    elif int(n) == n:
        pantalla.insert(0, str(int(n)))
    else:
        pantalla.insert(0, str(n))
    i = len(pantalla.get()) + 1
    last_eq = True


pantalla = Entry(window, font="Calibri 14", justify="right")
pantalla.grid(row=0, column=0, columnspan=4)
pantalla.insert(0, "0")

last_op = Entry(window)

button_0 = Button(window, text="0", width=button_width * 3 - 3, height=button_height, relief="groove",
                  command=lambda: add(0))
button_1 = Button(window, text="1", width=button_width, height=button_height, relief="groove", command=lambda: add(1))
button_2 = Button(window, text="2", width=button_width, height=button_height, relief="groove", command=lambda: add(2))
button_3 = Button(window, text="3", width=button_width, height=button_height, relief="groove", command=lambda: add(3))
button_4 = Button(window, text="4", width=button_width, height=button_height, relief="groove", command=lambda: add(4))
button_5 = Button(window, text="5", width=button_width, height=button_height, relief="groove", command=lambda: add(5))
button_6 = Button(window, text="6", width=button_width, height=button_height, relief="groove", command=lambda: add(6))
button_7 = Button(window, text="7", width=button_width, height=button_height, relief="groove", command=lambda: add(7))
button_8 = Button(window, text="8", width=button_width, height=button_height, relief="groove", command=lambda: add(8))
button_9 = Button(window, text="9", width=button_width, height=button_height, relief="groove", command=lambda: add(9))
button_c = Button(window, text="C", width=button_width, height=button_height, relief="groove",
                  command=lambda: action_c())
button_div = Button(window, text="/", width=button_width, height=button_height, relief="groove",
                    command=lambda: op('/'))
button_prod = Button(window, text="x", width=button_width, height=button_height, relief="groove",
                     command=lambda: op('*'))
button_sum = Button(window, text="+", width=button_width, height=button_height, relief="groove",
                    command=lambda: op('+'))
button_diff = Button(window, text="-", width=button_width, height=button_height, relief="groove",
                     command=lambda: op('-'))
button_point = Button(window, text=".", width=button_width, height=button_height, relief="groove",
                      command=lambda: op('.'))
button_openpar = Button(window, text="(", width=button_width, height=button_height, relief="groove",
                        command=lambda: op('('))
button_closepar = Button(window, text=")", width=button_width, height=button_height, relief="groove",
                         command=lambda: op(')'))
button_equals = Button(window, text="=", width=button_width, height=button_height, relief="groove",
                       command=lambda: action_equals())

button_c.grid(row=1, column=0, padx=button_padx, pady=button_pady)
button_openpar.grid(row=1, column=1, padx=button_padx, pady=button_pady)
button_closepar.grid(row=1, column=2, padx=button_padx, pady=button_pady)
button_div.grid(row=1, column=3, padx=button_padx, pady=button_pady)

button_7.grid(row=2, column=0, padx=button_padx, pady=button_pady)
button_8.grid(row=2, column=1, padx=button_padx, pady=button_pady)
button_9.grid(row=2, column=2, padx=button_padx, pady=button_pady)
button_prod.grid(row=2, column=3, padx=button_padx, pady=button_pady)

button_4.grid(row=3, column=0, padx=button_padx, pady=button_pady)
button_5.grid(row=3, column=1, padx=button_padx, pady=button_pady)
button_6.grid(row=3, column=2, padx=button_padx, pady=button_pady)
button_diff.grid(row=3, column=3, padx=button_padx, pady=button_pady)

button_1.grid(row=4, column=0, padx=button_padx, pady=button_pady)
button_2.grid(row=4, column=1, padx=button_padx, pady=button_pady)
button_3.grid(row=4, column=2, padx=button_padx, pady=button_pady)
button_sum.grid(row=4, column=3, padx=button_padx, pady=button_pady)

button_0.grid(row=5, column=0, padx=button_padx, pady=button_pady, columnspan=2)
button_point.grid(row=5, column=2, padx=button_padx, pady=button_pady)
button_equals.grid(row=5, column=3, padx=button_padx, pady=button_pady)

window.mainloop()


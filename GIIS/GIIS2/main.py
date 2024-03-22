import tkinter as tk
import math
import numpy as np

window = tk.Tk()
window.title("Графический редактор")
window.geometry("500x400")

canvas = tk.Canvas(window, width=400, height=300)
canvas.pack()

center_x, center_y = 0, 0
is_drawing = False

def start_drawing(event):
    global is_drawing, center_x, center_y
    is_drawing = True
    center_x = event.x
    center_y = event.y

def draw(event):
    if not is_drawing:
        return

    curve_type = curve_type_var.get()
    a = abs(event.x - center_x)
    b = abs(event.y - center_y)
    step = 1 / max(a, b)

    canvas.delete("all")

    for angle in range(0, int(2 * 3.14159 / step)):
        angle_rad = angle * step
        x, y = 0, 0

        if curve_type == "circle":
            x = int(center_x + a * math.cos(angle_rad))
            y = int(center_y + a * math.sin(angle_rad))
        elif curve_type == "ellipse":
            x = int(center_x + a * math.cos(angle_rad))
            y = int(center_y + b * math.sin(angle_rad))
        elif curve_type == "hyperbola":
            x = int(center_x + a / math.cos(angle_rad))
            y = int(center_y + b * math.tan(angle_rad))
        elif curve_type == "parabola":
            x = int(center_x + a * angle_rad)
            y = int(center_y + b * angle_rad ** 2)
            x2 = int(center_x - a * angle_rad)
            y2 = y
            canvas.create_rectangle(x2, y2, x2 + 1, y2 + 1)

        canvas.create_rectangle(x, y, x + 1, y + 1)  # Рисуем пиксель

def stop_drawing(event):
    global is_drawing
    is_drawing = False

def clear_canvas():
    canvas.delete("all")

canvas.bind("<Button-1>", start_drawing)
canvas.bind("<B1-Motion>", draw)
canvas.bind("<ButtonRelease-1>", stop_drawing)

curve_type_var = tk.StringVar()
curve_type_var.set("circle")

curve_type_menu = tk.OptionMenu(window, curve_type_var, "circle", "ellipse", "hyperbola", "parabola")
curve_type_menu.pack()

clear_button = tk.Button(window, text="Очистить", command=clear_canvas)
clear_button.pack()

window.mainloop()
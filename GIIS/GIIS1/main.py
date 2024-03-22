import tkinter as tk
from tkinter import messagebox

class GraphicsEditor:
    def __init__(self, root):
        self.root = root
        self.canvas_width = 800
        self.canvas_height = 600
        self.canvas = tk.Canvas(self.root, width=self.canvas_width, height=self.canvas_height)
        self.canvas.pack()

        self.algorithm = None
        self.debug_mode = False
        self.start_x = None
        self.start_y = None

        self.create_menu()
        self.create_toolbar()

        self.canvas.bind("<Button-1>", self.on_canvas_click)

    def create_menu(self):
        menubar = tk.Menu(self.root)
        algorithms_menu = tk.Menu(menubar, tearoff=0)
        algorithms_menu.add_command(label="ЦДА", command=self.select_dda_algorithm)
        algorithms_menu.add_command(label="Брезенхем", command=self.select_bresenham_algorithm)
        algorithms_menu.add_command(label="Ву", command=self.select_wu_algorithm)
        menubar.add_cascade(label="Отрезки", menu=algorithms_menu)
        self.root.config(menu=menubar)

    def create_toolbar(self):
        toolbar = tk.Frame(self.root)
        toolbar.pack(side=tk.TOP, fill=tk.X)

        debug_button = tk.Button(toolbar, text="Отладочный режим", command=self.toggle_debug_mode)
        debug_button.pack(side=tk.LEFT)

        clear_button = tk.Button(toolbar, text="Очистить", command=self.clear_canvas)
        clear_button.pack(side=tk.LEFT)

    def clear_canvas(self):
        self.canvas.delete("all")

    def select_dda_algorithm(self):
        self.algorithm = "ЦДА"
        messagebox.showinfo("Алгоритм", "Выбран алгоритм ЦДА для построения отрезков.")

    def select_bresenham_algorithm(self):
        self.algorithm = "Брезенхем"
        messagebox.showinfo("Алгоритм", "Выбран целочисленный алгоритм Брезенхема для построения отрезков.")

    def select_wu_algorithm(self):
        self.algorithm = "Ву"
        messagebox.showinfo("Алгоритм", "Выбран алгоритм Ву для построения отрезков.")

    def toggle_debug_mode(self):
        self.debug_mode = not self.debug_mode
        if self.debug_mode:
            messagebox.showinfo("Отладочный режим", "Включен отладочный режим.")
        else:
            messagebox.showinfo("Отладочный режим", "Выключен отладочный режим.")

    def on_canvas_click(self, event):
        if self.start_x is None and self.start_y is None:
            self.start_x = event.x
            self.start_y = event.y
        else:
            self.draw_line(event.x, event.y)
            self.start_x = None
            self.start_y = None

    def draw_line(self, end_x, end_y):
        if self.algorithm is None:
            messagebox.showerror("Ошибка", "Не выбран алгоритм для построения отрезков.")
            return

        if self.algorithm == "ЦДА":
            self.dda_line(self.start_x, self.start_y, end_x, end_y)
        elif self.algorithm == "Брезенхем":
            self.bresenham_line(self.start_x, self.start_y, end_x, end_y)
        elif self.algorithm == "Ву":
            self.wu_line(self.start_x, self.start_y, end_x, end_y)

    def dda_line(self, x0, y0, x1, y1):
        dx = x1 - x0
        dy = y1 - y0
        steps = max(abs(dx), abs(dy))
        x_increment = dx / steps
        y_increment = dy / steps

        x = x0
        y = y0

        for _ in range(steps + 1):
            self.canvas.create_rectangle(x, y, x, y, width=1)
            if self.debug_mode:
                self.canvas.update()
                self.canvas.after(50)  # Задержка для отображения пошаговогорешения
            x += x_increment
            y += y_increment

    def bresenham_line(self, x0, y0, x1, y1):
        dx = abs(x1 - x0)
        dy = abs(y1 - y0)
        sx = -1 if x0 > x1 else 1
        sy = -1 if y0 > y1 else 1

        if dx > dy:
            err = dx / 2
        else:
            err = -dy / 2

        while True:
            self.canvas.create_rectangle(x0, y0, x0, y0, width=1)
            if self.debug_mode:
                self.canvas.update()
                self.canvas.after(50)  # Задержка для отображения пошагового решения

            if x0 == x1 and y0 == y1:
                break

            e2 = err

            if e2 > -dx:
                err -= dy
                x0 += sx

            if e2 < dy:
                err += dx
                y0 += sy

    def wu_line(self, x0, y0, x1, y1):
        dx = x1 - x0
        dy = y1 - y0

        if abs(dx) > abs(dy):
            steps = abs(dx)
        else:
            steps = abs(dy)

        x_increment = dx / steps
        y_increment = dy / steps

        x = x0
        y = y0

        for _ in range(steps + 1):
            i = int(x)
            j = int(y)

            self.canvas.create_rectangle(i, j, i, j, width=1)
            if self.debug_mode:
                self.canvas.update()
                self.canvas.after(50)  # Задержка для отображения пошагового решения

            i = int(x + x_increment)
            j = int(y + y_increment)

            self.canvas.create_rectangle(i, j, i, j, width=1)
            if self.debug_mode:
                self.canvas.update()
                self.canvas.after(50)  # Задержка для отображения пошагового решения

            x += x_increment
            y += y_increment

if __name__ == "__main__":
    root = tk.Tk()
    root.title("Графический редактор")
    editor = GraphicsEditor(root)
    root.mainloop()
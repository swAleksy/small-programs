import os
import tkinter as tk
import tkinter.messagebox as tkmb
import tkinter.filedialog as tkfd

class Notepad:
    root = tk.Tk()
    
    width = 800
    height = 400

    text_area = tk.Text(root)
    menu_bar = tk.Menu(root)
    file_menu = tk.Menu(menu_bar, tearoff=0)
    file_about = tk.Menu(menu_bar, tearoff=0)
    menu_bar.add_cascade(label="File", menu=file_menu)
    menu_bar.add_cascade(label="About", menu=file_about)

    _file = None

    def __init__(self):
        self.root.title("Notepad")
        # self.root.geometry(str(self.width) + "x"+ str(self.height))

        screenWidth = self.root.winfo_screenwidth()
        screenHeight = self.root.winfo_screenheight()
        
        left = (screenWidth / 2) - (self.width / 2) 
         
        top = (screenHeight / 2) - (self.height /2) 
        self.root.geometry('%dx%d+%d+%d' % (self.width, self.height, left, top))

        self.root.grid_rowconfigure(0, weight=1)
        self.root.grid_columnconfigure(0, weight=1) 

        self.text_area.grid(sticky= tk.N + tk.E + tk.S + tk.W)
        self.file_menu.add_command(label="New", command=self.new_file)
         
        self.file_menu.add_command(label="Open", command=self.open_file)
         
        self.file_menu.add_command(label="Save", command=self.save_file)

        self.file_menu.add_command(label="Find", command=self.find_in_file) 

        self.file_menu.add_separator()                                         
        self.file_menu.add_command(label="Exit", command=self.quit_app)

        self.root.config(menu=self.menu_bar)
    
    def new_file(self):
        self._file = None
        self.root.title("Notepad")
        self.text_area.delete(1.0, tk.END)

    def open_file(self):
        new_file = tkfd.askopenfilename(title="Open a file", initialdir='/', defaultextension=".txt", filetypes=[("Text Documents", "*.txt")])
        if new_file == "":
            self._file = None
        else:
            self._file = new_file
            self.root.title("Notepad - "+os.path.basename(self._file))
            self.text_area.delete(1.0, tk.END)

            file = open(self._file,"r")
            self.text_area.insert(1.0, file.read())
    
            file.close()

    def save_file(self):
        
        if self._file == None:
            self._file = tkfd.asksaveasfilename(initialfile="Untitled.txt", defaultextension=".txt", filetypes=[("All Files","*.*"),("Text Documents","*.txt")])
            file = open(self._file, "w")
            file.write(self.text_area.get(1.0, tk.END))
            file.close()

            self.root.title(os.path.basename("Notepad - "+self._file))

        else:
            file = open(self._file, "w")
            file.write(self.text_area.get(1.0, tk.END))
            file.close()

    def find_in_file(self):
        top = tk.Toplevel()
        top.title("Find")

        root_x = self.root.winfo_rootx()
        root_y = self.root.winfo_rooty()
        
        top_y = root_y + 10  
        top.update_idletasks()
        top_x = root_x + self.width - 50 - top.winfo_width()
        top.geometry(f"+{top_x}+{top_y}")

        tk.Label(top,text='Text to find:').pack(side = tk.LEFT) 
        text_to_find = tk.Entry(top)
        text_to_find.pack(side=tk.LEFT)
        
        btn = tk.Button(top, text="find", command=lambda: self.find(text_to_find.get()))
        btn.pack(side=tk.RIGHT)
        

    def find(self, text_to_find):
        found_index = self.text_area.search(text_to_find, '1.0', stopindex=tk.END)
        if found_index:
            self.text_area.mark_set(tk.INSERT, found_index + "+%dc" % len(text_to_find))
            
    def quit_app(self):
        self.root.destroy()

    def run(self):
       self.root.mainloop()

notepad = Notepad()
notepad.run()
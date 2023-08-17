import ctypes
from tkinter import *


def fill_array(size):
    if (not isinstance(size, int)):
        return
    if (size < 0):
        return
    lib = ctypes.CDLL('./libs/my_module.so')
    _fill_array = lib.fill_array
    _fill_array.argtypes = (
        ctypes.c_int, ctypes.POINTER(ctypes.c_int))
    _fill_array.restype = None

    array_res = (ctypes.c_int * size)()

    _fill_array(size, array_res)

    return list(array_res)


def extend_array(arr_old, num):
    if (not isinstance(arr_old, list)):
        return
    if (not isinstance(num, int)):
        return

    lib = ctypes.CDLL('./libs/my_module.so')
    _extend_array = lib.extend_array
    _extend_array.argtypes = (ctypes.c_int, ctypes.POINTER(ctypes.c_int), ctypes.POINTER(ctypes.c_int),
                              ctypes.c_int)
    _extend_array.restype = ctypes.c_int

    cur_size = len(arr_old)
    arr1 = (ctypes.c_int * cur_size)(*arr_old)

    new_size = _extend_array(cur_size, arr1, None, 0)

    print(new_size)

    arr2 = (ctypes.c_int * new_size)()

    new_size = _extend_array(cur_size, arr1, arr2, num)

    return list(arr2)


def extend_array2(arr_old, num):
    if (not isinstance(arr_old, list)):
        return
    if (not isinstance(num, int)):
        return

    lib = ctypes.CDLL('./libs/my_module.so')
    _extend_array2 = lib.extend_array2
    _extend_array2.argtypes = (ctypes.c_int, ctypes.POINTER(ctypes.c_int), ctypes.POINTER(ctypes.c_int),
                               ctypes.c_int)
    _extend_array2.restype = ctypes.c_int

    cur_size = len(arr_old)
    arr1 = (ctypes.c_int * cur_size)(*arr_old)

    # new_size = _extend_array2(cur_size, arr1, arr2, 0)

    # print(new_size)

    arr2 = (ctypes.c_int * cur_size * 2)()

    _extend_array2(cur_size, arr1, arr2, num)

    return list(arr2)


def arr_of_prime_nums():
    size_str = input1.get()

    try:
        size = int(size_str)

        if (size < 1):
            res.delete(0, END)
            return

        arr = fill_array(size)

        arr_str = ' '.join(str(num) for num in arr)
        res.delete(0, END)
        res.insert(END, arr_str)
    except:
        res.delete(0, END)


def arr_with_insert_num():
    insert_num_str = input3.get()

    try:
        insert_num = int(insert_num_str)
    except:
        return

    arr_str = input2.get()

    try:
        arr = [int(num) for num in arr_str.split()]
    except:
        res.delete(0, END)
        return

    new_arr = extend_array(arr, insert_num)

    arr_str = ' '.join(str(num) for num in new_arr)
    res.delete(0, END)
    res.insert(END, arr_str)


window = Tk()
window.title('')
window.geometry('900x700')

arr_size_text = Label(text='Размер массива')
arr_size_text.place(x=100, y=70, width=700, height=30)

prime_nums = StringVar()
input1 = Entry(
    window, textvariable=prime_nums)
input1.place(x=85, y=100, width=700, height=40)

b1 = Button(window, text='Создать', command=lambda: arr_of_prime_nums())
b1.place(x=200, y=170, width=500, height=30)


input_arr_for_even_text = Label(
    text='Массив')
input_arr_for_even_text.place(x=100, y=270, width=700, height=30)

arr_for_even = StringVar()
input2 = Entry(
    window, textvariable=arr_for_even)
input2.place(x=85, y=300, width=700, height=40)


text2 = Label(
    text='Число вставки после четного')
text2.place(x=100, y=370, width=700, height=30)

num_for_even = StringVar()
input3 = Entry(
    window, textvariable=num_for_even, font=('Arial Bold', 16))
input3.place(x=85, y=400, width=700, height=40)

b2 = Button(
    window, text='Вставить число', command=lambda: arr_with_insert_num())
b2.place(x=200, y=470, width=500, height=30)

res = Entry(window)
res.place(x=100, y=600, width=700, height=40)

window.mainloop()

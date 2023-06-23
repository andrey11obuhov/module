#include <Python.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
static PyObject *caesar_cipher(PyObject *self, PyObject *args){
    const char *str1;
    char *str;
    int key;

    if (!PyArg_ParseTuple(args, "s", &str1)) {
        return NULL;
    }
    if (!PyArg_ParseTuple(args, "i", &key)) {
        return NULL;
    }
	str=str1;



  for (int i = 0; i < strlen(str); i++) {
    if (str[i] >= 'a' && str[i] <= 'z') {
      str[i] = (str[i] - 'a' + key) % 26 + 'a';
    } else if (str[i] >= 'A' && str[i] <= 'Z') {
      str[i] = (str[i] - 'A' + key) % 26 + 'A';
    }
  }

return Py_BuildValue("s", str);}

	int get_alphabet_index(char c) {

  if (c >= 'a' && c <= 'z') {
    return c - 'a';
  } else if (c >= 'A' && c <= 'Z') {
    return c - 'A';
  } else {
    return -1;
  }
}

static PyObject *transposition_cipher(PyObject *self, PyObject *args){
    const char *str;
    int key;

    if (!PyArg_ParseTuple(args, "s", &str)) {
        return NULL;
    }
    if (!PyArg_ParseTuple(args, "i", &key)) {
        return NULL;
    }
	char *input;
	char *output;

	for (int i = 0; i < strlen(input); i++) {

    int index = get_alphabet_index(input[i]);

    int output_index = (index + key) % ALPHABET_SIZE;

    output[output_index] = input[i];
  }
	return Py_BuildValue("s", output);}


static PyObject *atbash_cipher(PyObject *self, PyObject *args){
    const char *str1;

    if (!PyArg_ParseTuple(args, "s", &str1)) {
        return NULL;
    }
    char *str=str1;
    for (int i = 0; i < strlen(str); i++) {
    if (str[i] >= 'a' && str[i] <= 'z') {
      str[i] = 'z' - (str[i] - 'a');
    } else if (str[i] >= 'A' && str[i] <= 'Z') {
      str[i] = 'Z' - (str[i] - 'A');
    }
  }

return Py_BuildValue("s", str);}


static PyObject *atbash_decoder(PyObject *self, PyObject *args){
    const char *str1;

    if (!PyArg_ParseTuple(args, "s", &str1)) {
        return NULL;
    }
    char *str=str1;
     char decoded[strlen(str)];

    for (int i = 0; i < strlen(str); i++)
    {
        int ascii = str[i];
        if (ascii >= 'A' && ascii <= 'Z')
        {
            ascii = ascii + 32;
            ascii = 'z' - (ascii - 'a');
        }
        decoded[i] = ascii;
    }
    return Py_BuildValue("s", decoded);}

static PyObject *vigenere_cipher(PyObject *self, PyObject *args){ /* Сортировка вставками */
    const char *str1;
    const char *key1;
    if (!PyArg_ParseTuple(args, "s", &str1, &key1)) {
        return NULL;
    }
    char *text=str1;
    char *key=key1;
    int i, j;
  for (i = 0; i < strlen(text); i++) {
    text[i] = (text[i] + key[i % strlen(key)]) % 26;
  }
  return Py_BuildValue("s", text);}


static PyObject *vigenere_decoder(PyObject *self, PyObject *args){
    const char *str1;
    const char *key1;
    if (!PyArg_ParseTuple(args, "s", &str1, &key1)) {
        return NULL;
    }
    char *str=str1;
    char *key=key1;

   char *decoded = malloc(strlen(str) + 1);
  for (int i = 0; i < strlen(str); i++) {
    char c = str[i];
    char k = key[i % strlen(key)];
    c -= k;
    if (c < 'a') {
      c += 26;
    }
    decoded[i] = c;
  }
  return Py_BuildValue("s", decoded);}



/* Массив структур, описывающий методы модуля */
static PyMethodDef ownmod_methods[] = {
    {
	"caesar_cipher", /* название функции внутри python */
	caesar_cipher, /* функция C */
	 METH_VARARGS, /* макрос, поясняющий, что функция у нас с аргументами */
	"caesar_cipher" /* документация для функции внутри python */
    },
    {
	"transposition_cipher", /* название функции внутри python */
	transposition_cipher, /* функция C */
	 METH_VARARGS, /* макрос, поясняющий, что функция у нас с аргументами */
	"transposition_cipher" /* документация для функции внутри python */
    },
    {
	"atbash_cipher", /* название функции внутри python */
	atbash_cipher, /* функция C */
	 METH_VARARGS, /* макрос, поясняющий, что функция у нас с аргументами */
	"atbash_cipher" /* документация для функции внутри python */
    },
    {
	"atbash_decoder", /* название функции внутри python */
	atbash_decoder, /* функция C */
	 METH_VARARGS, /* макрос, поясняющий, что функция у нас с аргументами */
	"atbash_decoder" /* документация для функции внутри python */
    },
    {
	"vigenere_cipher", /* название функции внутри python */
	vigenere_cipher, /* функция C */
	 METH_VARARGS, /* макрос, поясняющий, что функция у нас с аргументами */
	"vigenere_cipher" /* документация для функции внутри python */
    },
    {
	"vigenere_decoder", /* название функции внутри python */
	vigenere_decoder, /* функция C */
	 METH_VARARGS, /* макрос, поясняющий, что функция у нас с аргументами */
	"vigenere_decoder" /* документация для функции внутри python */
    },
    { NULL, NULL, 0, NULL }
};


/* Cтруктура, которая описывает непосредственно сам модуль */
static PyModuleDef simple_module = {
    PyModuleDef_HEAD_INIT, /* обязательный макрос */
    "ciphers", /* sortingMethods.__name__ */
    "interesting siphers", /* siphers.__doc__ */
    -1,
    ownmod_methods, /* передаем массив с методами модуля */
    NULL,NULL,NULL
};


/* Создание самого модуля */
PyMODINIT_FUNC PyInit_ciphers(void)
{
    PyObject* m;
    /* создаем модуль */
    m = PyModule_Create(&simple_module);
    /* если все корректно, то эта проверка не проходит */
    if (m == NULL)
        return NULL;
    return m;
}

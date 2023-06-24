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
	char *input=str;
	char *output;

	for (int i = 0; i < strlen(input); i++) {

    int index = get_alphabet_index(input[i]);

    int output_index = (index + key) % 26;

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

static PyObject *vigenere_cipher(PyObject *self, PyObject *args){ /* Ñîðòèðîâêà âñòàâêàìè */
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



/* Ìàññèâ ñòðóêòóð, îïèñûâàþùèé ìåòîäû ìîäóëÿ */
static PyMethodDef ownmod_methods[] = {
    {
	"caesar_cipher", /* íàçâàíèå ôóíêöèè âíóòðè python */
	caesar_cipher, /* ôóíêöèÿ C */
	 METH_VARARGS, /* ìàêðîñ, ïîÿñíÿþùèé, ÷òî ôóíêöèÿ ó íàñ ñ àðãóìåíòàìè */
	"caesar_cipher" /* äîêóìåíòàöèÿ äëÿ ôóíêöèè âíóòðè python */
    },
    {
	"transposition_cipher", /* íàçâàíèå ôóíêöèè âíóòðè python */
	transposition_cipher, /* ôóíêöèÿ C */
	 METH_VARARGS, /* ìàêðîñ, ïîÿñíÿþùèé, ÷òî ôóíêöèÿ ó íàñ ñ àðãóìåíòàìè */
	"transposition_cipher" /* äîêóìåíòàöèÿ äëÿ ôóíêöèè âíóòðè python */
    },
    {
	"atbash_cipher", /* íàçâàíèå ôóíêöèè âíóòðè python */
	atbash_cipher, /* ôóíêöèÿ C */
	 METH_VARARGS, /* ìàêðîñ, ïîÿñíÿþùèé, ÷òî ôóíêöèÿ ó íàñ ñ àðãóìåíòàìè */
	"atbash_cipher" /* äîêóìåíòàöèÿ äëÿ ôóíêöèè âíóòðè python */
    },
    {
	"atbash_decoder", /* íàçâàíèå ôóíêöèè âíóòðè python */
	atbash_decoder, /* ôóíêöèÿ C */
	 METH_VARARGS, /* ìàêðîñ, ïîÿñíÿþùèé, ÷òî ôóíêöèÿ ó íàñ ñ àðãóìåíòàìè */
	"atbash_decoder" /* äîêóìåíòàöèÿ äëÿ ôóíêöèè âíóòðè python */
    },
    {
	"vigenere_cipher", /* íàçâàíèå ôóíêöèè âíóòðè python */
	vigenere_cipher, /* ôóíêöèÿ C */
	 METH_VARARGS, /* ìàêðîñ, ïîÿñíÿþùèé, ÷òî ôóíêöèÿ ó íàñ ñ àðãóìåíòàìè */
	"vigenere_cipher" /* äîêóìåíòàöèÿ äëÿ ôóíêöèè âíóòðè python */
    },
    {
	"vigenere_decoder", /* íàçâàíèå ôóíêöèè âíóòðè python */
	vigenere_decoder, /* ôóíêöèÿ C */
	 METH_VARARGS, /* ìàêðîñ, ïîÿñíÿþùèé, ÷òî ôóíêöèÿ ó íàñ ñ àðãóìåíòàìè */
	"vigenere_decoder" /* äîêóìåíòàöèÿ äëÿ ôóíêöèè âíóòðè python */
    },
    { NULL, NULL, 0, NULL }
};


/* Còðóêòóðà, êîòîðàÿ îïèñûâàåò íåïîñðåäñòâåííî ñàì ìîäóëü */
static PyModuleDef simple_module = {
    PyModuleDef_HEAD_INIT, /* îáÿçàòåëüíûé ìàêðîñ */
    "ciphers", /* sortingMethods.__name__ */
    "interesting siphers", /* siphers.__doc__ */
    -1,
    ownmod_methods, /* ïåðåäàåì ìàññèâ ñ ìåòîäàìè ìîäóëÿ */
    NULL,NULL,NULL
};


/* Ñîçäàíèå ñàìîãî ìîäóëÿ */
PyMODINIT_FUNC PyInit_ciphers(void)
{
    PyObject* m;
    /* ñîçäàåì ìîäóëü */
    m = PyModule_Create(&simple_module);
    /* åñëè âñå êîððåêòíî, òî ýòà ïðîâåðêà íå ïðîõîäèò */
    if (m == NULL)
        return NULL;
    return m;
}

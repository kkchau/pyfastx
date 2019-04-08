#ifndef PYFASTX_FASTX_H
#define PYFASTX_FASTX_H
#include <zlib.h>
#include <Python.h>
#include <sqlite3.h>
#include "kseq.h"
#include "zran.h"

KSEQ_DECLARE(gzFile)

//make sequence iterator
typedef struct {
	PyObject_HEAD
	
	//gzip open file handle
	gzFile gzfp;

	//file open handle
	FILE* fd;
	
	//kseqs for reading from fasta
	kseq_t* kseqs;
	
	//sqlite3 handle for index
	sqlite3* db;
	
	//fasta or fastq file path and name
	char* file_name;

	//sqlite3 index file path and name
	char* index_file;

	//always output capital sequence
	int capital;

	//is gzip compressed file
	int gzip;

	//gzip random access index
	zran_index_t *gzip_index;

} FastxObject;

extern PyTypeObject pyfastx_FastxType;

PyObject* build_index(FastxObject *self, PyObject *args, PyObject *kwargs);
PyObject* test(FastxObject *self, PyObject *args);
PyObject* fastx_tp_new(PyTypeObject *type, PyObject *args, PyObject *kwargs);
PyObject* fastx_tp_iter(FastxObject *self);
PyObject* fastx_tp_next(FastxObject *self);
void fastx_tp_dealloc(FastxObject *self);

#endif
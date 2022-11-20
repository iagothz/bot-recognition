// This file implements the IExternalConnection Interface and Gateway for Python.
// Generated by makegw.py

#include "stdafx.h"
#include "PythonCOM.h"
#include "PythonCOMServer.h"
#include "PyIExternalConnection.h"

// @doc - This file contains autoduck documentation
// ---------------------------------------------------
//
// Interface Implementation

PyIExternalConnection::PyIExternalConnection(IUnknown *pdisp) : PyIUnknown(pdisp) { ob_type = &type; }

PyIExternalConnection::~PyIExternalConnection() {}

/* static */ IExternalConnection *PyIExternalConnection::GetI(PyObject *self)
{
    return (IExternalConnection *)PyIUnknown::GetI(self);
}

// @pymethod int|PyIExternalConnection|AddConnection|Increments an object's count of its strong external connections
// (links).
PyObject *PyIExternalConnection::AddConnection(PyObject *self, PyObject *args)
{
    IExternalConnection *pIEC = GetI(self);
    if (pIEC == NULL)
        return NULL;
    // @pyparm int|extconn||Type of external connection to the object. The only type of external connection currently
    // supported by this interface is strong, which means that the object must remain alive as long as this external
    // connection exists. Strong external connections are represented by the value EXTCONN_STRONG = 0x0001, which is
    // defined in the enumeration EXTCON
    // @pyparm int|reserved|0|A reserved parameter
    DWORD extconn;
    DWORD reserved = 0;
    if (!PyArg_ParseTuple(args, "i|i:AddConnection", &extconn, &reserved))
        return NULL;
    PY_INTERFACE_PRECALL;
    DWORD rc = pIEC->AddConnection(extconn, reserved);
    PY_INTERFACE_POSTCALL;
    // @rdesc The result is the number of reference counts on the object; used for debugging purposes only.
    return PyLong_FromLong(rc);
}

// @pymethod int|PyIExternalConnection|ReleaseConnection|Decrements an object's count of its strong external connections
// (references).
PyObject *PyIExternalConnection::ReleaseConnection(PyObject *self, PyObject *args)
{
    IExternalConnection *pIEC = GetI(self);
    if (pIEC == NULL)
        return NULL;
    // @pyparm int|extconn||Type of external connection
    // @pyparm int|reserved||A reserved parameter.
    // @pyparm int|fLastReleaseCloses||TRUE specifies that if the connection being released is the last external lock on
    // the object, the object should close. FALSE specifies that the object should remain open until closed by the user
    // or another process.
    DWORD extconn;
    DWORD reserved;
    BOOL fLastReleaseCloses;
    if (!PyArg_ParseTuple(args, "iii:ReleaseConnection", &extconn, &reserved, &fLastReleaseCloses))
        return NULL;
    PY_INTERFACE_PRECALL;
    DWORD rc = pIEC->ReleaseConnection(extconn, reserved, fLastReleaseCloses);
    PY_INTERFACE_POSTCALL;
    // @rdesc The result is the number of reference counts on the object; used for debugging purposes only.
    return PyLong_FromLong(rc);
}

// @object PyIExternalConnection|A Python wrapper for a COM IExternalConnection interface.
// @comm The IExternalConnection interface manages a server object's count of marshaled, or external, connections. A
// server that maintains such a count can detect when it has no external connections and shut itself down in an orderly
// fashion.
static struct PyMethodDef PyIExternalConnection_methods[] = {
    {"AddConnection", PyIExternalConnection::AddConnection,
     1},  // @pymeth AddConnection|Increments an object's count of its strong external connections (links).
    {"ReleaseConnection", PyIExternalConnection::ReleaseConnection,
     1},  // @pymeth ReleaseConnection|Decrements an object's count of its strong external connections (references).
    {NULL}};

PyComTypeObject PyIExternalConnection::type("PyIExternalConnection",
                                            &PyIUnknown::type,  // @base PyIExternalConnection|PyIUnknown
                                            sizeof(PyIExternalConnection), PyIExternalConnection_methods,
                                            GET_PYCOM_CTOR(PyIExternalConnection));
// ---------------------------------------------------
//
// Gateway Implementation

DWORD STDMETHODCALLTYPE PyGExternalConnection::AddConnection(
    /* [in] */ DWORD extconn,
    /* [in] */ DWORD reserved)
{
    PY_GATEWAY_METHOD;
    return InvokeViaPolicy("AddConnection", NULL, "ii", extconn, reserved);
}

DWORD STDMETHODCALLTYPE PyGExternalConnection::ReleaseConnection(
    /* [in] */ DWORD extconn,
    /* [in] */ DWORD reserved,
    /* [in] */ BOOL fLastReleaseCloses)
{
    PY_GATEWAY_METHOD;
    return InvokeViaPolicy("ReleaseConnection", NULL, "iii", extconn, reserved, fLastReleaseCloses);
}
// This file implements the IEnumDebugPropertyInfo Interface and Gateway for Python.
// Generated by makegw.py

#include "stdafx.h"
#include "PyIEnumDebugPropertyInfo.h"

// @doc - This file contains autoduck documentation
BOOL PyObject_AsDebugPropertyInfo(PyObject *, DebugPropertyInfo *pInfo);
PyObject *PyObject_FromDebugPropertyInfo(const DebugPropertyInfo *pInfo);
// ---------------------------------------------------
//
// Interface Implementation

PyIEnumDebugPropertyInfo::PyIEnumDebugPropertyInfo(IUnknown *pdisp) : PyIUnknown(pdisp) { ob_type = &type; }

PyIEnumDebugPropertyInfo::~PyIEnumDebugPropertyInfo() {}

/* static */ IEnumDebugPropertyInfo *PyIEnumDebugPropertyInfo::GetI(PyObject *self)
{
    return (IEnumDebugPropertyInfo *)PyIUnknown::GetI(self);
}

// @pymethod object|PyIEnumDebugPropertyInfo|Next|Retrieves a specified number of items in the enumeration sequence.
PyObject *PyIEnumDebugPropertyInfo::Next(PyObject *self, PyObject *args)
{
    long celt = 1;
    // @pyparm int|num|1|Number of items to retrieve.
    if (!PyArg_ParseTuple(args, "|l:Next", &celt))
        return NULL;

    IEnumDebugPropertyInfo *pIEDebugPropertyInfo = GetI(self);
    if (pIEDebugPropertyInfo == NULL)
        return NULL;

    DebugPropertyInfo *rgVar = new DebugPropertyInfo[celt];
    if (rgVar == NULL) {
        PyErr_SetString(PyExc_MemoryError, "allocating result DebugPropertyInfos");
        return NULL;
    }

    int i;
    /*	for ( i = celt; i--; )
            // *** possibly init each structure element???
    */

    ULONG celtFetched = 0;
    PY_INTERFACE_PRECALL;
    HRESULT hr = pIEDebugPropertyInfo->Next(celt, rgVar, &celtFetched);
    PY_INTERFACE_POSTCALL;
    if (HRESULT_CODE(hr) != ERROR_NO_MORE_ITEMS && FAILED(hr)) {
        delete[] rgVar;
        return PyCom_BuildPyException(hr, pIEDebugPropertyInfo, IID_IEnumDebugPropertyInfo);
    }

    PyObject *result = PyTuple_New(celtFetched);
    if (result != NULL) {
        for (i = celtFetched; i--;) {
            PyObject *ob = PyObject_FromDebugPropertyInfo(rgVar + i);
            if (ob == NULL) {
                Py_DECREF(result);
                result = NULL;
                break;
            }
            PyTuple_SET_ITEM(result, i, ob);
        }
    }

    /*	for ( i = celtFetched; i--; )
            // *** possibly cleanup each structure element???
    */
    delete[] rgVar;
    return result;
}

// @pymethod |PyIEnumDebugPropertyInfo|Skip|Skips over the next specified elementes.
PyObject *PyIEnumDebugPropertyInfo::Skip(PyObject *self, PyObject *args)
{
    long celt;
    if (!PyArg_ParseTuple(args, "l:Skip", &celt))
        return NULL;

    IEnumDebugPropertyInfo *pIEDebugPropertyInfo = GetI(self);
    if (pIEDebugPropertyInfo == NULL)
        return NULL;

    PY_INTERFACE_PRECALL;
    HRESULT hr = pIEDebugPropertyInfo->Skip(celt);
    PY_INTERFACE_POSTCALL;
    if (FAILED(hr))
        return PyCom_BuildPyException(hr, pIEDebugPropertyInfo, IID_IEnumDebugPropertyInfo);

    Py_INCREF(Py_None);
    return Py_None;
}

// @pymethod |PyIEnumDebugPropertyInfo|Reset|Resets the enumeration sequence to the beginning.
PyObject *PyIEnumDebugPropertyInfo::Reset(PyObject *self, PyObject *args)
{
    if (!PyArg_ParseTuple(args, ":Reset"))
        return NULL;

    IEnumDebugPropertyInfo *pIEDebugPropertyInfo = GetI(self);
    if (pIEDebugPropertyInfo == NULL)
        return NULL;

    PY_INTERFACE_PRECALL;
    HRESULT hr = pIEDebugPropertyInfo->Reset();
    PY_INTERFACE_POSTCALL;
    if (FAILED(hr))
        return PyCom_BuildPyException(hr, pIEDebugPropertyInfo, IID_IEnumDebugPropertyInfo);

    Py_INCREF(Py_None);
    return Py_None;
}

// @pymethod <o PyIEnumDebugPropertyInfo>|PyIEnumDebugPropertyInfo|Clone|Creates another enumerator that contains the
// same enumeration state as the current one
PyObject *PyIEnumDebugPropertyInfo::Clone(PyObject *self, PyObject *args)
{
    if (!PyArg_ParseTuple(args, ":Clone"))
        return NULL;

    IEnumDebugPropertyInfo *pIEDebugPropertyInfo = GetI(self);
    if (pIEDebugPropertyInfo == NULL)
        return NULL;

    IEnumDebugPropertyInfo *pClone;
    PY_INTERFACE_PRECALL;
    HRESULT hr = pIEDebugPropertyInfo->Clone(&pClone);
    PY_INTERFACE_POSTCALL;
    if (FAILED(hr))
        return PyCom_BuildPyException(hr, pIEDebugPropertyInfo, IID_IEnumDebugPropertyInfo);

    return PyCom_PyObjectFromIUnknown(pClone, IID_IEnumDebugPropertyInfo, FALSE);
}

// @pymethod int|PyIEnumDebugPropertyInfo|GetCount|Obtains the number of items
PyObject *PyIEnumDebugPropertyInfo::GetCount(PyObject *self, PyObject *args)
{
    if (!PyArg_ParseTuple(args, ":GetCount"))
        return NULL;

    IEnumDebugPropertyInfo *pIEDebugPropertyInfo = GetI(self);
    if (pIEDebugPropertyInfo == NULL)
        return NULL;
    ULONG ret;
    PY_INTERFACE_PRECALL;
    HRESULT hr = pIEDebugPropertyInfo->GetCount(&ret);
    PY_INTERFACE_POSTCALL;
    if (FAILED(hr))
        return PyCom_BuildPyException(hr, pIEDebugPropertyInfo, IID_IEnumDebugPropertyInfo);

    return PyLong_FromLong(ret);
}

// @object PyIEnumDebugPropertyInfo|A Python interface to IEnumDebugPropertyInfo
static struct PyMethodDef PyIEnumDebugPropertyInfo_methods[] = {
    {"Next", PyIEnumDebugPropertyInfo::Next,
     1},  // @pymeth Next|Retrieves a specified number of items in the enumeration sequence.
    {"Skip", PyIEnumDebugPropertyInfo::Skip, 1},    // @pymeth Skip|Skips over the next specified elementes.
    {"Reset", PyIEnumDebugPropertyInfo::Reset, 1},  // @pymeth Reset|Resets the enumeration sequence to the beginning.
    {"Clone", PyIEnumDebugPropertyInfo::Clone,
     1},  // @pymeth Clone|Creates another enumerator that contains the same enumeration state as the current one.
    {"GetCount", PyIEnumDebugPropertyInfo::GetCount, 1},  // @pymeth GetCount|Obtains the number of items
    {NULL}};

PyComTypeObject PyIEnumDebugPropertyInfo::type("PyIEnumDebugPropertyInfo", &PyIUnknown::type,
                                               sizeof(PyIEnumDebugPropertyInfo), PyIEnumDebugPropertyInfo_methods,
                                               GET_PYCOM_CTOR(PyIEnumDebugPropertyInfo));

// ---------------------------------------------------
//
// Gateway Implementation

STDMETHODIMP PyGEnumDebugPropertyInfo::Next(
    /* [in] */ ULONG celt,
    /* [length_is][size_is][out] */ DebugPropertyInfo __RPC_FAR *rgVar,
    /* [out] */ ULONG __RPC_FAR *pCeltFetched)
{
    PY_GATEWAY_METHOD;
    PyObject *result;
    Py_ssize_t len;
    HRESULT hr = InvokeViaPolicy("Next", &result, "i", celt);
    if (FAILED(hr))
        return hr;

    if (!PySequence_Check(result))
        goto error;
    len = PyObject_Length(result);
    if (len == -1)
        goto error;
    if (len > (Py_ssize_t)celt)
        len = celt;

    if (pCeltFetched)
        *pCeltFetched = PyWin_SAFE_DOWNCAST(len, Py_ssize_t, ULONG);

    Py_ssize_t i;
    for (i = 0; i < len; ++i) {
        PyObject *ob = PySequence_GetItem(result, i);
        if (ob == NULL)
            goto error;

        if (!PyObject_AsDebugPropertyInfo(ob, &rgVar[i])) {
            Py_DECREF(result);
            return PyCom_SetCOMErrorFromPyException(IID_IEnumDebugPropertyInfo);
        }
    }

    Py_DECREF(result);

    return len < (Py_ssize_t)celt ? S_FALSE : S_OK;

error:
    PyErr_Clear();  // just in case
    Py_DECREF(result);
    return PyCom_HandleIEnumNoSequence(IID_IEnumDebugPropertyInfo);
}

STDMETHODIMP PyGEnumDebugPropertyInfo::Skip(
    /* [in] */ ULONG celt)
{
    PY_GATEWAY_METHOD;
    return InvokeViaPolicy("Skip", NULL, "i", celt);
}

STDMETHODIMP PyGEnumDebugPropertyInfo::Reset(void)
{
    PY_GATEWAY_METHOD;
    return InvokeViaPolicy("Reset");
}

STDMETHODIMP PyGEnumDebugPropertyInfo::Clone(
    /* [out] */ IEnumDebugPropertyInfo __RPC_FAR *__RPC_FAR *ppEnum)
{
    PY_GATEWAY_METHOD;
    PyObject *result;
    HRESULT hr = InvokeViaPolicy("Clone", &result);
    if (FAILED(hr))
        return hr;

    /*
    ** Make sure we have the right kind of object: we should have some kind
    ** of IUnknown subclass wrapped into a PyIUnknown instance.
    */
    if (!PyIBase::is_object(result, &PyIUnknown::type)) {
        /* the wrong kind of object was returned to us */
        Py_DECREF(result);
        return PyCom_SetCOMErrorFromSimple(E_FAIL, IID_IEnumDebugPropertyInfo);
    }

    /*
    ** Get the IUnknown out of the thing. note that the Python ob maintains
    ** a reference, so we don't have to explicitly AddRef() here.
    */
    IUnknown *punk = ((PyIUnknown *)result)->m_obj;
    if (!punk) {
        /* damn. the object was released. */
        Py_DECREF(result);
        return PyCom_SetCOMErrorFromSimple(E_FAIL, IID_IEnumDebugPropertyInfo);
    }

    /*
    ** Get the interface we want. note it is returned with a refcount.
    ** This QI is actually going to instantiate a PyGEnumDebugPropertyInfo.
    */
    Py_BEGIN_ALLOW_THREADS hr = punk->QueryInterface(IID_IEnumDebugPropertyInfo, (LPVOID *)ppEnum);
    Py_END_ALLOW_THREADS

        /* done with the result; this DECREF is also for <punk> */
        Py_DECREF(result);

    return PyCom_CheckIEnumNextResult(hr, IID_IEnumDebugPropertyInfo);
}

STDMETHODIMP PyGEnumDebugPropertyInfo::GetCount(
    /* [out] */ ULONG __RPC_FAR *pcelt)
{
    if (pcelt == NULL)
        return E_POINTER;
    PY_GATEWAY_METHOD;
    PyObject *result;
    HRESULT hr = InvokeViaPolicy("GetCount", &result);
    if (FAILED(hr))
        return hr;
    *pcelt = PyLong_AsLong(result);
    Py_DECREF(result);
    return PyCom_SetCOMErrorFromPyException(IID_IEnumDebugPropertyInfo);
}

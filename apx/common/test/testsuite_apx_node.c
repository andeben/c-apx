//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include "CuTest.h"
#include "apx_node.h"
#ifdef MEM_LEAK_CHECK
#include "CMemLeak.h"
#endif


//////////////////////////////////////////////////////////////////////////////
// CONSTANTS AND DATA TYPES
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// LOCAL FUNCTION PROTOTYPES
//////////////////////////////////////////////////////////////////////////////
static void test_apx_node_create(CuTest* tc);

//////////////////////////////////////////////////////////////////////////////
// GLOBAL VARIABLES
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// LOCAL VARIABLES
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
// GLOBAL FUNCTIONS
//////////////////////////////////////////////////////////////////////////////


CuSuite* testSuite_apx_node(void)
{
   CuSuite* suite = CuSuiteNew();

   SUITE_ADD_TEST(suite, test_apx_node_create);

   return suite;
}

//////////////////////////////////////////////////////////////////////////////
// LOCAL FUNCTIONS
//////////////////////////////////////////////////////////////////////////////
static void test_apx_node_create(CuTest* tc)
{
   apx_node_t node;
   void **ptr;
   apx_port_t *port;
   apx_node_create(&node,"Dummy");
   apx_node_createRequirePort(&node,"PV_VehicleSpeed","S",0);
   apx_node_createRequirePort(&node,"PS_ParkBrakeActuationFalue","C(0,3)",0);
   apx_node_resolvePortSignatures(&node);
   CuAssertIntEquals(tc,2,adt_ary_length(&node.requirePortList));
   ptr = adt_ary_get(&node.requirePortList,0);
   CuAssertPtrNotNull(tc,ptr);
   port = (apx_port_t*) *ptr;
   CuAssertIntEquals(tc,2,apx_dataSignature_packLen(&port->derivedDsg));
   CuAssertIntEquals(tc,0,apx_port_getPortIndex(port));
   ptr = adt_ary_get(&node.requirePortList,1);
   CuAssertPtrNotNull(tc,ptr);
   port = (apx_port_t*) *ptr;
   CuAssertIntEquals(tc,1,apx_dataSignature_packLen(&port->derivedDsg));
   CuAssertIntEquals(tc,1,apx_port_getPortIndex(port));
   apx_node_destroy(&node);
}


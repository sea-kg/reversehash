#include <bna_var.h>

BNAVar::BNAVar() {
   m_bVal = false;
}
		
// -----------------------------------------------------------------

bool BNAVar::val(){
    return m_bVal;
}

// -----------------------------------------------------------------

void BNAVar::val(bool bVal){
    m_bVal = bVal;
}

// -----------------------------------------------------------------


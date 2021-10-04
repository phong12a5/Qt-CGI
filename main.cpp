///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <QCoreApplication>
#include <AppMain.h>
#include <CkGlobal.h>

CkGlobal glob;

bool unlockChilkat();

int main(int intArguments, char* charArguments[])
{
        // Initializet the application
        QCoreApplication qcaGeoData(intArguments, charArguments);
        // Unlock chilkat
        unlockChilkat();

        AppMain myapp;
        myapp.handleRequest();

        qcaGeoData.exit();
}

bool unlockChilkat() {
    bool success_global = glob.UnlockBundle("AUTFRM.CB4082023_Pz2Ry7az86p4");
    if (success_global != true) {
        return false;
    }

    int status = glob.get_UnlockStatus();
    if (status == 2) {
        return true;
    } else {
        return false;
    }
}

#include "inc/OStream.h"

class Integer {


};

char logo[] = "\
                                                                                \
             ######  ##    ##  ######  ######## ######## ##     ##              \
            ##    ##  ##  ##  ##    ##    ##    ##       ###   ###              \
            ##         ####   ##          ##    ##       #### ####              \
             ######     ##     ######     ##    ######   ## ### ##              \
                  ##    ##          ##    ##    ##       ##     ##              \
            ##    ##    ##    ##    ##    ##    ##       ##     ##              \
             ######     ##     ######     ##    ######## ##     ##              \
                                                                                ";


extern "C" void loader() {
	OStream cout;
	char endl = '\n';
	
	cout.SetBackgroundColor(cout.Blue);
	cout << logo;
	cout.SetBackgroundColor(cout.LightGrey);
	cout << "                                                                                ";
	cout.SetBackgroundColor(cout.Black);


	cout << "Cau amigo!" << endl;
	cout << "root>";
	for(;;) cout << Keyborad::read();
	for(;;);
}
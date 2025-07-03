#include "FE.h"
#include <QApplication>
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    FerrumUi window;
    window.show();
    return app.exec();
}

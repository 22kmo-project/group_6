#include "myurl.h"

MyUrl::MyUrl()
{

}

QString MyUrl::getBaseUrl()
{
    return base_url;
}
QString MyUrl::base_url{
    "http://localhost:3000"
    //"https://...." Voi tarvittaessa vaihtaa.
};

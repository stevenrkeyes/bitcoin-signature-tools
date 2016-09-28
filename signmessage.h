#ifndef _signmessage_h
#define _signmessage_h

#include <string>

std::string signmessage(std::string strSecret, std::string strMessage);

#include "util.h"
#include "base58.h"
#include "signmessage.h"

extern const string strMessageMagic;

//signmessage <base58privatekey> <message>
//Sign a message using a Bitcoin private key.
string signmessage(string strSecret, string strMessage) {
    
    CBitcoinSecret vchSecret;
    bool fGood = vchSecret.SetString(strSecret);

    if (!fGood) {
        printf("Private key is not good\n");
        return "";
    }

    CKey key;
    bool fCompressed;
    CSecret csecret = vchSecret.GetSecret(fCompressed);
    key.SetSecret(csecret, fCompressed);

    CHashWriter ss(0);
    ss << strMessageMagic;
    ss << strMessage;

    vector<unsigned char> vchSig;
    if (!key.SignCompact(ss.GetHash(), vchSig)) {
        printf("Sign failed\n");
        return "";
    }
    
    return EncodeBase64(&vchSig[0], vchSig.size()).c_str();
}

#endif

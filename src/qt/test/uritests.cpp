// Copyright (c) 2009-2014 The Bitcoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "uritests.h"

#include "guiutil.h"
#include "walletmodel.h"

#include <QUrl>

void URITests::uriTests()
{
    SendCoinsRecipient rv;
    QUrl uri;
    uri.setUrl(QString("reddcoin:RdXd6m9nZ6GsUA6ZXLJjiyuKeS3vvsS7NX?req-dontexist="));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("reddcoin:RdXd6m9nZ6GsUA6ZXLJjiyuKeS3vvsS7NX?dontexist="));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("RdXd6m9nZ6GsUA6ZXLJjiyuKeS3vvsS7NX"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 0);

    uri.setUrl(QString("reddcoin:RdXd6m9nZ6GsUA6ZXLJjiyuKeS3vvsS7NX?label=Wikipedia Example Address"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("RdXd6m9nZ6GsUA6ZXLJjiyuKeS3vvsS7NX"));
    QVERIFY(rv.label == QString("Wikipedia Example Address"));
    QVERIFY(rv.amount == 0);

    uri.setUrl(QString("reddcoin:RdXd6m9nZ6GsUA6ZXLJjiyuKeS3vvsS7NX?amount=0.001"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("RdXd6m9nZ6GsUA6ZXLJjiyuKeS3vvsS7NX"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 100000);

    uri.setUrl(QString("reddcoin:RdXd6m9nZ6GsUA6ZXLJjiyuKeS3vvsS7NX?amount=1.001"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("RdXd6m9nZ6GsUA6ZXLJjiyuKeS3vvsS7NX"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 100100000);

    uri.setUrl(QString("reddcoin:RdXd6m9nZ6GsUA6ZXLJjiyuKeS3vvsS7NX?amount=100&label=Wikipedia Example"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("RdXd6m9nZ6GsUA6ZXLJjiyuKeS3vvsS7NX"));
    QVERIFY(rv.amount == 10000000000LL);
    QVERIFY(rv.label == QString("Wikipedia Example"));

    uri.setUrl(QString("reddcoin:RdXd6m9nZ6GsUA6ZXLJjiyuKeS3vvsS7NX?message=Wikipedia Example Address"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("RdXd6m9nZ6GsUA6ZXLJjiyuKeS3vvsS7NX"));
    QVERIFY(rv.label == QString());

    QVERIFY(GUIUtil::parseBitcoinURI("reddcoin://RdXd6m9nZ6GsUA6ZXLJjiyuKeS3vvsS7NX?message=Wikipedia Example Address", &rv));
    QVERIFY(rv.address == QString("RdXd6m9nZ6GsUA6ZXLJjiyuKeS3vvsS7NX"));
    QVERIFY(rv.label == QString());

    uri.setUrl(QString("reddcoin:RdXd6m9nZ6GsUA6ZXLJjiyuKeS3vvsS7NX?req-message=Wikipedia Example Address"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("reddcoin:RdXd6m9nZ6GsUA6ZXLJjiyuKeS3vvsS7NX?amount=1,000&label=Wikipedia Example"));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("reddcoin:RdXd6m9nZ6GsUA6ZXLJjiyuKeS3vvsS7NX?amount=1,000.0&label=Wikipedia Example"));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));
}

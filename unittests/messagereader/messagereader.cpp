#include "KDSoapMessage.h"
#include "KDSoapMessageReader_p.h"
#include <QtTest/QtTest>

class TestMessageReader : public QObject
{
    Q_OBJECT
private Q_SLOTS:

    void testLineBreak()
    {
        const QByteArray xmlNoWhitespace =
        "<soapenv:Envelope xmlns:soapenv=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:dat=\"http://www.27seconds.com/Holidays/US/Dates/\">"
        "<soapenv:Header/>"
        "<soapenv:Body>"
        "<dat:GetEaster>"
        "<dat:year>2011</dat:year>"
        "</dat:GetEaster>"
        "</soapenv:Body>"
        "</soapenv:Envelope>";

        const QByteArray xmlWithWhitespace =
        "<soapenv:Envelope xmlns:soapenv=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:dat=\"http://www.27seconds.com/Holidays/US/Dates/\">\n"
        "<soapenv:Header/>\n"
        "  <soapenv:Body>\n"
        "    <dat:GetEaster>\n"
        "      <dat:year>2011</dat:year>\n"
        "    </dat:GetEaster>\n"
        "  </soapenv:Body>\n"
        "</soapenv:Envelope>\n";

        const KDSoapMessageReader reader;
        QString ns;
        KDSoapMessage msg;
        KDSoapHeaders headers;
        const KDSoapMessageReader::XmlError err = reader.xmlToMessage( xmlNoWhitespace, &msg, &ns, &headers );
        QCOMPARE( err, KDSoapMessageReader::NoError );
        QVERIFY( !msg.isFault() );
        QCOMPARE( msg.name(), QLatin1String("GetEaster") );

        const KDSoapMessageReader reader2;
        QString ns2;
        KDSoapMessage msg2;
        KDSoapHeaders headers2;

        const KDSoapMessageReader::XmlError err2 = reader.xmlToMessage( xmlWithWhitespace, &msg2, &ns2, &headers2 );
        QCOMPARE( err2, KDSoapMessageReader::NoError );
        QCOMPARE( msg2.name(), QLatin1String("GetEaster") );

        if ( !( msg == msg2 ) ) {
            QEXPECT_FAIL( "", "There is different whitespace in the (unused) value of getEaster", Continue );
            qDebug() << msg;
            qDebug() << msg2;
        }
    }
};

QTEST_MAIN(TestMessageReader)

#include "messagereader.moc"

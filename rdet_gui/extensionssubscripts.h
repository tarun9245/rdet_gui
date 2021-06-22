#ifndef EXTENSIONSSUBSCRIPTS_H
#define EXTENSIONSSUBSCRIPTS_H
#include <QString>
#include "metahandler.h"
#include <QDebug>
class extensionsSubScripts
{
private:
    metaHandler *m;
    QString *rdetPath;
    QString *hardware;
    QString *inputPath, *outputPath;
    QString *vmlinuxPath, *metaPath;
public:
    extensionsSubScripts();
    extensionsSubScripts(metaHandler *meta, QString *rdetDir);
    void setdumpsPath(QString*);
    void setOutputPath(QString*);
    void setAppsPath(QString*);
    void setHardware(QString *hw);
    QString run_qtf();
    QString dcc_wrapper();
    QString delete_qtf_json();
    QString register_dump_parser();
    QString cpuss_dump_parser();
    QString system_parameters_wrapper();
    QString dcc_gladiator_parser_v2();
    QString ddr_debugging();
    QString ddr_process_dumps();
    QString sensein_noc();
    QString shlog_parser();
    QString noc_decode_dcc();
    QString cxttable_decode();
    QString qtf_parser();
    QString qtf_signature();
    QString logcat_parser();
    QString task_state_parser();
    QString tlb_dump_parser();
};

#endif // EXTENSIONSSUBSCRIPTS_H

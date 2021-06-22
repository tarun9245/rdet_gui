#include "extensionssubscripts.h"

extensionsSubScripts::extensionsSubScripts()
{

}

extensionsSubScripts::extensionsSubScripts(metaHandler *meta, QString *rdetDir)
{
    m = meta;
    rdetPath = rdetDir;
}

void extensionsSubScripts::setdumpsPath(QString *dumpsPath) {
    inputPath = dumpsPath;
}

void extensionsSubScripts::setAppsPath(QString *appsPath) {
    vmlinuxPath = appsPath;
}

void extensionsSubScripts::setOutputPath(QString *outDir) {
    outputPath = outDir;
}

void extensionsSubScripts::setHardware(QString *hw) {
    hardware = hw;
}

QString extensionsSubScripts::run_qtf()
{
    QString cmd = "py -3 " + *rdetPath + "\\extensions\\support_scripts\\run_qtf\\run_qtf.py ";
    qDebug()<<"Inside QString extensionsSubScripts::run_qtf()";
    cmd += *inputPath + " --json --target " + m->getChipSet();
    cmd += " -o " + *outputPath;
    cmd += " --metaPath " + *metaPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString extensionsSubScripts::run_qtf()";
    return cmd;
}

QString extensionsSubScripts::dcc_wrapper()
{
    QString cmd = "py -3 " + *rdetPath + "\\extensions\\support_scripts\\dcc_parser\\dcc_wrapper.py ";
    qDebug()<<"Inside QString extensionsSubScripts::dcc_wrapper()";
    cmd += *inputPath + " -a " + *outputPath + "\\qtf.json";
    cmd += " --target " + m->getChipSet();
    cmd += " -o " + *outputPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString extensionsSubScripts::dcc_wrapper()";
    return cmd;
}

QString extensionsSubScripts::delete_qtf_json()
{
    QString cmd = "py -3 " + *rdetPath + "\\extensions\\support_scripts\\run_qtf\\delete_qtf_json.py ";
    qDebug()<<"Inside QString extensionsSubScripts::delete_qtf_json()";
    cmd += *outputPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString extensionsSubScripts::delete_qtf_json()";
    return cmd;
}

QString extensionsSubScripts::register_dump_parser()
{
    QString cmd = "py -3 " + *rdetPath + "\\extensions\\support_scripts\\dcc_parser\\register_dump_parser.py ";
    qDebug()<<"Inside QString extensionsSubScripts::register_dump_parser()";
    cmd += *inputPath + " " + *outputPath;
    cmd += " --target " + m->getChipSet();
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString extensionsSubScripts::register_dump_parser()";
    return cmd;
}

QString extensionsSubScripts::cpuss_dump_parser()
{
    QString cmd = "py -3 " + *rdetPath + "\\extensions\\support_scripts\\cpuss_dump_parser\\cpuss_dump_parser.py ";
    qDebug()<<"Inside QString extensionsSubScripts::cpuss_dump_parser()";
    cmd += *inputPath + " " + *outputPath;
    cmd += " --target " + m->getChipSet();
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString extensionsSubScripts::cpuss_dump_parser()";
    return cmd;
}

QString extensionsSubScripts::system_parameters_wrapper()
{
    QString cmd = "py -3 " + *rdetPath + "\\extensions\\support_scripts\\system_parameters\\system_parms_wrapper.py ";
    qDebug()<<"Inside QString extensionsSubScripts::system_parameters_wrapper()";
    cmd += *inputPath + " " + *metaPath + " --o " + *outputPath;
    cmd += " --target " + m->getChipSet() + " --hw_version Y";
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString extensionsSubScripts::system_parameters_wrapper()";
    return cmd;
}

QString extensionsSubScripts::dcc_gladiator_parser_v2()
{
    QString cmd = "py -3 " + *rdetPath + "\\extensions\\support_scripts\\dcc_gladiator_parser\\dcc_gladiator_parser_v2.py ";
    qDebug()<<"Inside QString extensionsSubScripts::dcc_gladiator_parser_v2()";
    cmd += *outputPath;
    cmd += " --target " + m->getChipSet();
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString extensionsSubScripts::dcc_gladiator_parser_v2()";
    return cmd;
}

QString extensionsSubScripts::ddr_debugging()
{
    QString cmd = "py -3 " + *rdetPath + "\\extensions\\support_scripts\\ddr_debugging\\ddr_debugging.py ";
    qDebug()<<"Inside QString extensionsSubScripts::ddr_debugging()";
    cmd += *outputPath;
    cmd += " --target " + m->getChipSet();
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString extensionsSubScripts::ddr_debugging()";
    return cmd;
}

QString extensionsSubScripts::ddr_process_dumps()
{
    QString cmd = "py -3 " + *rdetPath + "\\extensions\\support_scripts\\DDR_process_dumps\\ddr_process_dumps_warpper.py ";
    qDebug()<<"Inside QString extensionsSubScripts::ddr_process_dumps()";
    cmd += *outputPath;
    cmd += " --target " + m->getChipSet();
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString extensionsSubScripts::ddr_process_dumps()";
    return cmd;
}

QString extensionsSubScripts::sensein_noc()
{
    QString cmd = "py -3 " + *rdetPath + "\\extensions\\support_scripts\\sensein_noc\\sensein_noc.py ";
    qDebug()<<"Inside QString extensionsSubScripts::sensein_noc()";
    cmd += *outputPath;
    cmd += " --target " + m->getChipSet();
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString extensionsSubScripts::sensein_noc()";
    return cmd;
}

QString extensionsSubScripts::shlog_parser()
{
    QString cmd = "py -3 " + *rdetPath + "\\extensions\\support_scripts\\qtf_parser\\shlog_parser.py ";
    qDebug()<<"Inside QString extensionsSubScripts::shlog_parser()";
    cmd += " --input " + *inputPath;
    cmd += " --output " + *outputPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString extensionsSubScripts::shlog_parser()";
    return cmd;
}

QString extensionsSubScripts::noc_decode_dcc()
{
    QString cmd = "py -3 " + *rdetPath + "\\extensions\\support_scripts\\noc_decode_dcc\\noc_decode_dcc.py ";
    qDebug()<<"Inside QString extensionsSubScripts::noc_decode_dcc()";
    cmd += " --input " + *inputPath;
    cmd += " --output " + *outputPath;
    cmd += " --target " + m->getChipSet();
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString extensionsSubScripts::noc_decode_dcc()";
    return cmd;
}

QString extensionsSubScripts::cxttable_decode()
{
    QString cmd = "py -3 " + *rdetPath + "\\extensions\\support_scripts\\context_table_parser\\cxttable_decode.py ";
    qDebug()<<"Inside QString extensionsSubScripts::cxttable_decode()";
    cmd += " --input " + *inputPath;
    cmd += " --output " + *outputPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString extensionsSubScripts::cxttable_decode()";
    return cmd;
}

QString extensionsSubScripts::qtf_parser()
{
    QString cmd = "py -3 " + *rdetPath + "\\extensions\\support_scripts\\qtf_parser\\qtf_parser.py ";
    qDebug()<<"Inside QString extensionsSubScripts::qtf_parser()";
    cmd += " --input " + *inputPath;
    cmd += " --output " + *outputPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString extensionsSubScripts::qtf_parser()";
    return cmd;
}

QString extensionsSubScripts::qtf_signature()
{
    QString cmd = "py -3 " + *rdetPath + "\\extensions\\support_scripts\\qtf_signature\\qtf_signature.py ";
    qDebug()<<"Inside QString extensionsSubScripts::qtf_signature()";
    cmd += " --input " + *inputPath;
    cmd += " --output " + *outputPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString extensionsSubScripts::qtf_signature()";
    return cmd;
}

QString extensionsSubScripts::logcat_parser()
{
    QString cmd = "py -3 " + *rdetPath + "\\extensions\\support_scripts\\logcat_parser\\logcat_parser.py ";
    qDebug()<<"Inside QString extensionsSubScripts::logcat_parser()";
    cmd += " --input " + *inputPath;
    cmd += " --output " + *outputPath;
    cmd += " --target " + m->getChipSet();
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString extensionsSubScripts::logcat_parser()";
    return cmd;
}

QString extensionsSubScripts::task_state_parser()
{
    QString cmd = "py -3 " + *rdetPath + "\\extensions\\support_scripts\\task_state_parser\\task_state_parser.py ";
    qDebug()<<"Inside QString extensionsSubScripts::task_state_parser()";
    cmd += " --input " + *inputPath;
    cmd += " --output " + *outputPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString extensionsSubScripts::task_state_parser()";
    return cmd;
}

QString extensionsSubScripts::tlb_dump_parser()
{
    QString cmd = "py -3 " + *rdetPath + "\\extensions\\support_scripts\\smmu_tlb_dump_parser\\tlb_dump_parser.py ";
    qDebug()<<"Inside QString extensionsSubScripts::tlb_dump_parser()";
    cmd += " --input " + *inputPath;
    cmd += " --output " + *outputPath;
    cmd += " --reduceddump N";
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString extensionsSubScripts::tlb_dump_parser()";
    return cmd;
}


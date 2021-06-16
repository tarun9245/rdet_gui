#include "libsubscripts.h"

libSubScripts::libSubScripts()
{

}

libSubScripts::libSubScripts(metaHandler *meta, QString *rdetDir)
{
    m = meta;
    rdetPath = rdetDir;
}

void libSubScripts::setdumpsPath(QString *dumpsPath) {
    inputPath = dumpsPath;
}

void libSubScripts::setAppsPath(QString *appsPath) {
    vmlinuxPath = appsPath;
}

void libSubScripts::setOutputPath(QString *outDir) {
    outputPath = outDir;
}

void libSubScripts::setHardware(QString *hw) {
    hardware = hw;
}
QString libSubScripts::ramparser(QString scripts)
{
    qDebug()<<"Inside QString libSubScripts::ramparserCmd()";
    QString cmd = "py -3 " + *rdetPath + "\\lib\\support_scripts\\ramparse\\ramparse_handler.py --vmlinux ";
    cmd += *vmlinuxPath + "vmlinux" + " --auto-dump " + *inputPath;
    cmd += " --force-hardware " + *hardware;
    cmd += " --dmesg --t32launcher --ddr-compare --clock-dump --check-for-panic --print-reserved-mem";
    cmd += " --lpm --regulator --ipc_logging --ipa --hotplug --kbootlog --wakeup";

    cmd += scripts;
    cmd += " -o " + *outputPath;
    if(m->getHypFileName() != "") {
        cmd += " --hyp " + m->getHypFilePath() + m->getHypFileName();
    }
    return cmd;
}

QString libSubScripts::module_symbol()
{
    QString cmd = "py -3 " + *rdetPath + "\\lib\\support_scripts\\module_symbol\\module_symbol.py ";
    qDebug()<<"Inside QString libSubScripts::module_symbolCmd()";
    cmd += *inputPath + " " + *vmlinuxPath + "vmlinux --target " + m->getChipSet();
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString libSubScripts::module_symbolCmd()";
    return cmd;
}

QString libSubScripts::platform_info()
{
    QString cmd = "py -3 " + *rdetPath + "\\lib\\support_scripts\\platform_info\\platform_info.py ";
    qDebug()<<"Inside QString libSubScripts::platform_infoCmd()";
    cmd += *inputPath + " -o " + *outputPath + " --target " + m->getChipSet();
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString libSubScripts::platform_infoCmd()";
    return cmd;
}

QString libSubScripts::dcc_wrapper()
{
    QString cmd = "py -3 " + *rdetPath + "\\lib\\support_scripts\\dcc_parser\\dcc_wrapper.py ";
    qDebug()<<"Inside QString libSubScripts::dcc_wrapperCmd()";
    cmd += *inputPath + " --target " + m->getChipSet() + " -o " + *outputPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString libSubScripts::dcc_wrapperCmd()";
    return cmd;
}

QString libSubScripts::task_stats()
{
    QString cmd = "py -3 " + *rdetPath + "\\lib\\support_scripts\\task_stats\\task_stats.py ";
    qDebug()<<"Inside QString libSubScripts::task_statsCmd()";
    cmd += *outputPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString libSubScripts::task_statsCmd()";
    return cmd;
}

QString libSubScripts::ddrCookies()
{
    QString cmd = "py -3 " + *rdetPath + "\\lib\\support_scripts\\DDRCookies\\DDRCookies.py ";
    qDebug()<<"Inside QString libSubScripts::ddrCookiesCmd()";
    cmd += *inputPath + " --output " + *outputPath;
    cmd += " -- target " + m->getChipSet();
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString libSubScripts::ddrCookiesCmd()";
    return cmd;
}

QString libSubScripts::excessive_logging()
{
    QString cmd = "py -3 " + *rdetPath + "\\lib\\support_scripts\\excessive_logging\\excessive_log_detection.py ";
    qDebug()<<"Inside QString libSubScripts::excessive_loggingCmd()";
    cmd += *outputPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString libSubScripts::excessive_loggingCmd()";
    return cmd;
}

QString libSubScripts::rdet_html_gen()
{
    QString cmd = "py -3 " + *rdetPath + "\\lib\\support_scripts\\rdet_html_gen\\rdet_html_gen.py ";
    qDebug()<<"Inside QString libSubScripts::rdet_html_genCmd()";
    cmd += *outputPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString libSubScripts::rdet_html_genCmd()";
    return cmd;
}

QString libSubScripts::read_power_collapse_cnt()
{
    QString cmd = "py -3 " + *rdetPath + "\\lib\\support_scripts\\read_power_collapse_cnt\\read_power_collapse_cnt.py ";
    qDebug()<<"Inside QString libSubScripts::read_power_collapse_cnt()";
    cmd += *inputPath + " --tz " + m->getTzPath();
    cmd += " --target " + m->getChipSet();
    cmd += " --outdir " + *outputPath;
    cmd += " --reduceddump N";
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString libSubScripts::read_power_collapse_cnt()";
    return cmd;
}

QString libSubScripts::tme_parser()
{
    QString cmd = "py -3 " + *rdetPath + "\\lib\\support_scripts\\tme_parser\\tme_parser.py ";
    qDebug()<<"Inside QString libSubScripts::tme_parser()";
    cmd += "-a " + *inputPath + " --meta " + metaPath;
    cmd += " --everything -o " + *outputPath;
    cmd += " --target " + m->getChipSet();
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString libSubScripts::tme_parser()";
    return cmd;
}

QString libSubScripts::tme_debugging()
{
    QString cmd = "py -3 " + *rdetPath + "\\lib\\support_scripts\\tme_parser\\tme_debugging.py ";
    qDebug()<<"Inside QString libSubScripts::tme_debugging()";
    cmd += *inputPath + " -o " + *outputPath;
    cmd += " --target " + m->getChipSet();
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString libSubScripts::tme_debugging()";
    return cmd;
}

QString libSubScripts::scandump_parser()
{
    QString cmd = "py -3 " + *rdetPath + "\\lib\\support_scripts\\scandump\\scandump_parser_helper.py ";
    qDebug()<<"Inside QString libSubScripts::scandump_parser()";
    cmd += *inputPath + " -o " + *outputPath;
    cmd += " --target " + m->getChipSet();
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString libSubScripts::scandump_parser()";
    return cmd;
}

QString libSubScripts::instr_fetcher()
{
    QString cmd = "py -3 " + *rdetPath + "\\lib\\support_scripts\\instr_fetcher\\instr_fetcher.py ";
    qDebug()<<"Inside QString libSubScripts::instr_fetcher()";
    cmd += *inputPath + " --o " + *outputPath;
    cmd += " " + m->getQseeFilePath() + m->getQseeFileName();
    cmd += " " + m->getMonFilePath() + m->getMonFileName();
    cmd += " " + m->getHypFilePath() + m->getHypFileName();
    cmd += " " + *vmlinuxPath + "\\vmlinux";
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString libSubScripts::instr_fetcher()";
    return cmd;
}

QString libSubScripts::bus_error_decoder()
{
    QString cmd = "py -3 " + *rdetPath + "\\lib\\support_scripts\\bus_error_decoders\\bus_error_decoder.py ";
    qDebug()<<"Inside QString libSubScripts::bus_error_decoder()";
    cmd += *inputPath + " --o " + *outputPath;
    cmd += " --target " + m->getChipSet();
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString libSubScripts::bus_error_decoder()";
    return cmd;
}

QString libSubScripts::smmu_fault_decoder()
{
    QString cmd = "py -3 " + *rdetPath + "\\lib\\support_scripts\\bus_error_decoders\\smmu_fault_decoder.py ";
    qDebug()<<"Inside QString libSubScripts::smmu_fault_decoder()";
    cmd += *outputPath;
    cmd += " --target " + m->getChipSet();
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString libSubScripts::smmu_fault_decoder()";
    return cmd;
}

QString libSubScripts::parse_panic_regs()
{
    QString cmd = "py -3 " + *rdetPath + "\\lib\\support_scripts\\parse_panic_regs\\create_panic_regs_cmm.py ";
    qDebug()<<"Inside QString libSubScripts::parse_panic_regs()";
    cmd += *inputPath + " " + *outputPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString libSubScripts::parse_panic_regs()";
    return cmd;
}

QString libSubScripts::edit_t32_shortcut()
{
    QString cmd = "py -3 " + *rdetPath + "\\lib\\support_scripts\\edit_t32_shortcut.py ";
    qDebug()<<"Inside QString libSubScripts::edit_t32_shortcut()";
    cmd += *outputPath;
    cmd += " " + m->getQseeFilePath() + m->getQseeFileName();
    cmd += " " + m->getMonFilePath() + m->getMonFileName();
    cmd += " " + m->getHypFilePath() + m->getHypFileName();
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString libSubScripts::edit_t32_shortcut()";
    return cmd;
}

QString libSubScripts::watchdog_parser()
{
    QString cmd = "py -3 " + *rdetPath + "\\lib\\support_scripts\\watchdog_parser\\watchdog.py ";
    qDebug()<<"Inside QString libSubScripts::watchdog_parser()";
    cmd += *outputPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString libSubScripts::watchdog_parser()";
    return cmd;
}

QString libSubScripts::ion_buf_analyzer()
{
    QString cmd = "py -3 " + *rdetPath + "\\lib\\support_scripts\\IONMem_parser\\ion_buf_analyzer.py ";
    qDebug()<<"Inside QString libSubScripts::ion_buf_analyzer()";
    cmd += *outputPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString libSubScripts::ion_buf_analyzer()";
    return cmd;
}

QString libSubScripts::wa_log()
{
    QString cmd = "py -3 " + *rdetPath + "\\lib\\support_scripts\\wa_log\\wa_log.pl ";
    qDebug()<<"Inside QString libSubScripts::wa_log()";
    cmd += *inputPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString libSubScripts::wa_log()";
    return cmd;
}

QString libSubScripts::lockup_parser()
{
    QString cmd = "py -3 " + *rdetPath + "\\lib\\support_scripts\\lockup_parser\\lockup.py ";
    qDebug()<<"Inside QString libSubScripts::lockup_parser()";
    cmd += *inputPath + " -o " + *outputPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString libSubScripts::lockup_parser()";
    return cmd;
}

QString libSubScripts::rtb_schedstat()
{
    QString cmd = "py -3 " + *rdetPath + "\\lib\\support_scripts\\RTB_Parser\\rtb_schedstat.py ";
    qDebug()<<"Inside QString libSubScripts::rtb_schedstat()";
    cmd += *outputPath + " --top=20";
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString libSubScripts::rtb_schedstat()";
    return cmd;
}

QString libSubScripts::memory_corruption()
{
    QString cmd = "py -3 " + *rdetPath + "\\lib\\support_scripts\\memory_corruption\\memory_corruption.py ";
    qDebug()<<"Inside QString libSubScripts::memory_corruption()";
    cmd += *inputPath + " --target " + *hardware;
    cmd += " " + *vmlinuxPath + "\\vmlinux -o " + *outputPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString libSubScripts::memory_corruption()";
    return cmd;
}

QString libSubScripts::iommu_pagetable()
{
    QString cmd = "py -3 " + *rdetPath + "\\lib\\support_scripts\\iommu_pagetable\\iommu_pagetable.py ";
    qDebug()<<"Inside QString libSubScripts::iommu_pagetable()";
    cmd += *inputPath + " --target " + hardware;
    cmd += " " + *vmlinuxPath + "\\vmlinux -o " + *outputPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString libSubScripts::iommu_pagetable()";
    return cmd;
}

QString libSubScripts::vidc_parse()
{
    QString cmd = "py -3 " + *rdetPath + "\\lib\\support_scripts\\vidc_parse\\vidc_parse.py ";
    qDebug()<<"Inside QString libSubScripts::vidc_parse()";
    cmd += *inputPath + " -o " + *outputPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString libSubScripts::vidc_parse()";
    return cmd;
}


QString libSubScripts::smmu_test_bus_decoding()
{
    QString cmd = "py -3 " + *rdetPath + "\\lib\\support_scripts\\bus_error_decoders\\smmu_test_bus_decoding.py ";
    qDebug()<<"Inside QString libSubScripts::smmu_test_bus_decoding()";
    cmd += *outputPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString libSubScripts::smmu_test_bus_decoding()";
    return cmd;
}

QString libSubScripts::memory_summarize()
{
    QString cmd = "py -3 " + *rdetPath + "\\lib\\support_scripts\\memory_summarize\\memory_summarize.py ";
    qDebug()<<"Inside QString libSubScripts::memory_summarize()";
    cmd += *inputPath + " " + *outputPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString libSubScripts::memory_summarize()";
    return cmd;
}

QString libSubScripts::tz_parser()
{
    QString cmd = "py -3 " + *rdetPath + "\\lib\\support_scripts\\tz_parser\\tz_parser.py ";
    qDebug()<<"Inside QString libSubScripts::tz_parser()";
    cmd += "--vmlinux " + *vmlinuxPath + "\\vmlinux";
    cmd += " --qsee " + m->getQseeFilePath() + m->getQseeFileName();
    cmd += " --mon " + m->getMonFilePath() + m->getMonFileName();
    cmd += " --hyp " + m->getHypFilePath() + m->getHypFileName();
    cmd += " --auto-dump " + *inputPath;
    cmd += " --force-hardware " + *hardware;
    cmd += " --everything -o " + *outputPath;
    cmd += " --reduceddump N";
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString libSubScripts::tz_parser()";
    return cmd;
}

QString libSubScripts::aop_parser()
{
    QString cmd = "py -3 " + *rdetPath + "\\lib\\support_scripts\\aop_parser\\aop_parser.py ";
    qDebug()<<"Inside QString libSubScripts::aop_parser()";
    cmd += "--aop " + m->getAopFilePath() + m->getAopFileName();
    cmd += " -i " + *inputPath;
    cmd += " --everything -o " + *outputPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString libSubScripts::aop_parser()";
    return cmd;
}

QString libSubScripts::cpucp_parser()
{
    QString cmd = "py -3 " + *rdetPath + "\\lib\\support_scripts\\cpucp_parser\\cpucp_parser.py ";
    qDebug()<<"Inside QString libSubScripts::cpucp_parser()";
    cmd += "-i " + *inputPath;
    cmd += " --meta " + *metaPath;
    cmd += " --everything -o " + *outputPath;
    cmd += " --target " + m->getChipSet();
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString libSubScripts::cpucp_parser()";
    return cmd;
}

QString libSubScripts::aop_script()
{
    QString cmd = "py -3 " + *rdetPath + "\\lib\\support_scripts\\aop_files_gen\\aop_script.py ";
    qDebug()<<"Inside QString libSubScripts::aop_script()";
    cmd += *inputPath + " --o " + *outputPath;
    cmd += " --aop " + m->getAopFilePath();
    cmd += " --target " + m->getChipSet();
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString libSubScripts::aop_script()";
    return cmd;
}

QString libSubScripts::merge_logs()
{
    QString cmd = "py -3 " + *rdetPath + "\\lib\\support_scripts\\merge_logs\\merge_logs.py ";
    qDebug()<<"Inside QString libSubScripts::merge_logs()";
    cmd += *outputPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString libSubScripts::merge_logs()";
    return cmd;
}

QString libSubScripts::ddr_freq_switch()
{
    QString cmd = "py -3 " + *rdetPath + "\\lib\\support_scripts\\ddr_freq_switch\\ddr_freq_switch.py ";
    qDebug()<<"Inside QString libSubScripts::ddr_freq_switch()";
    cmd += *inputPath + " --o " + *outputPath;
    cmd += " --target " + m->getChipSet();
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString libSubScripts::ddr_freq_switch()";
    return cmd;
}

QString libSubScripts::arc_stuck_debug()
{
    QString cmd = "py -3 " + *rdetPath + "\\lib\\support_scripts\\arc_stuck\\arc_stuck_debug.py ";
    qDebug()<<"Inside QString libSubScripts::arc_stuck_debug()";
    cmd += *inputPath + " " + metaPath;
    cmd += " --target " + m->getChipSet();
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString libSubScripts::arc_stuck_debug()";
    return cmd;
}

QString libSubScripts::split_tasks()
{
    QString cmd = "py -3 " + *rdetPath + "\\lib\\support_scripts\\split_tasks\\split_tasks.py ";
    qDebug()<<"Inside QString libSubScripts::split_tasks()";
    cmd += *inputPath + " -o " + *outputPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString libSubScripts::split_tasks()";
    return cmd;
}

QString libSubScripts::hypvm_traces()
{
    QString cmd = "py -3 " + *rdetPath + "\\lib\\support_scripts\\hymvm_traces\\hyp_parser.py ";
    qDebug()<<"Inside QString libSubScripts::hypvm_traces()";
    cmd += "--meta " + *metaPath;
    cmd += " --hyp " + m->getHypFilePath() + m->getHypFileName();
    cmd += " --auto-dump " + *inputPath;
    cmd += " --64-bit --target " + m->getChipSet();
    cmd += " -o " + *outputPath;
    cmd += " --reduceddump N";
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString libSubScripts::hypvm_traces()";
    return cmd;
}

QString libSubScripts::edac_decoder()
{
    QString cmd = "py -3 " + *rdetPath + "\\lib\\support_scripts\\edac_decoder\\edac_decoder.py ";
    qDebug()<<"Inside QString libSubScripts::edac_decoder()";
    cmd += *inputPath + " -o " + *outputPath;
    cmd += " --target " + m->getChipSet();
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString libSubScripts::edac_decoder()";
    return cmd;
}

QString libSubScripts::ddr_data()
{
    QString cmd = "py -3 " + *rdetPath + "\\lib\\support_scripts\\ddr_data\\ddr_data.py ";
    qDebug()<<"Inside QString libSubScripts::ddr_data()";
    cmd += *inputPath + " -o " + *outputPath;
    cmd += " --target " + m->getChipSet();
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString libSubScripts::ddr_data()";
    return cmd;
}

QString libSubScripts::consolidated_core_summary()
{
    QString cmd = "py -3 " + *rdetPath + "\\lib\\support_scripts\\consolidated_core_summary\\consolidated_core_summary.py ";
    qDebug()<<"Inside QString libSubScripts::consolidated_core_summary()";
    cmd += *inputPath + " -o " + *outputPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString libSubScripts::consolidated_core_summary()";
    return cmd;
}

QString libSubScripts::issue_signature_detector()
{
    QString cmd = "py -3 " + *rdetPath + "\\lib\\support_scripts\\issue_signature_detector\\issue_signature_detector.py ";
    qDebug()<<"Inside QString libSubScripts::issue_signature_detector()";
    cmd += *outputPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString libSubScripts::issue_signature_detector()";
    return cmd;
}

QString libSubScripts::lpm_merge()
{
    QString cmd = "py -3 " + *rdetPath + "\\lib\\support_scripts\\lpm_merge\\lpm_merge.py ";
    qDebug()<<"Inside QString libSubScripts::lpm_merge()";
    cmd += *outputPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString libSubScripts::lpm_merge()";
    return cmd;
}


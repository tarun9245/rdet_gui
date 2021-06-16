#ifndef LIBSUBSCRIPTS_H
#define LIBSUBSCRIPTS_H
#include "metahandler.h"
#include <QString>
#include <QDebug>

class libSubScripts
{
private:
    metaHandler *m;
    QString *rdetPath;
    QString *hardware;
    QString *inputPath, *outputPath;
    QString *vmlinuxPath, *metaPath;
public:
    libSubScripts();
    libSubScripts(metaHandler *meta, QString *rdetDir);
    void setdumpsPath(QString*);
    void setOutputPath(QString*);
    void setAppsPath(QString*);
    void setHardware(QString *hw);
    QString ramparser(QString scripts);
    QString tz_parser();
    QString module_symbol();
    QString platform_info();
    QString dcc_wrapper();
    QString task_stats();
    QString excessive_logging();
    QString ramparser_svm();
    QString ddrCookies();
    QString rdet_html_gen();
    QString read_power_collapse_cnt();
    QString tme_parser();
    QString tme_debugging();
    QString scandump_parser();
    QString instr_fetcher();
    QString bus_error_decoder();
    QString smmu_fault_decoder();
    QString parse_panic_regs();
    QString edit_t32_shortcut();
    QString watchdog_parser();
    QString ion_buf_analyzer();
    QString wa_log();
    QString lockup_parser();
    QString rtb_schedstat();
    QString memory_corruption();
    QString iommu_pagetable();
    QString vidc_parse();
    QString smmu_test_bus_decoding();
    QString memory_summarize();
    QString aop_parser();
    QString cpucp_parser();
    QString aop_script();
    QString merge_logs();
    QString ddr_freq_switch();
    QString arc_stuck_debug();
    QString split_tasks();
    QString hypvm_traces();
    QString ddr_data();
    QString edac_decoder();
    QString consolidated_core_summary();
    QString issue_signature_detector();
    QString lpm_merge();
};

#endif // LIBSUBSCRIPTS_H

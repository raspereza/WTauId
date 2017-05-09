#!bin/sh

# For trigger efficiencies
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer.conf SingleMuon_Run2016 20


./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf WJetsToLNu_13TeV-madgraphMLM-ext2-v1 10
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf WJetsToLNu_13TeV-madgraphMLM-v1 10
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8 10
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8 10
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8 10
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8 10

./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf WJetsToLNu_HT-70To100_13TeV-madgraphMLM-pythia8 10
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf WJetsToLNu_HT-100To200_13TeV-madgraphMLM-pythia8 10
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf WJetsToLNu_HT-200To400_13TeV-madgraphMLM-pythia8 10
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf WJetsToLNu_HT-400To600_13TeV-madgraphMLM-pythia8 10
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf WJetsToLNu_HT-600To800_13TeV-madgraphMLM-pythia8 10
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf WJetsToLNu_HT-800To1200_13TeV-madgraphMLM-pythia8 10


# For fake rate (no trigger efficiencies need to be included)
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer.conf JetHT_Run2016 20

# For n_EWK (including trigger efficiencies)
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer.conf MET_Run2016 10
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf WJetsToLNu_13TeV-madgraphMLM 10
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf TTJets_13TeV-powheg 5
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf ST_t-channel_top_4f_inclusiveDecays_13TeV-powheg 5
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powheg 5
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf ST_tW_top_5f_inclusiveDecays_13TeV-powheg 5
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg 5
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf VVTo2L2Nu_13TeV_amcatnloFXFX 10
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf WWToLNuQQ_13TeV_powheg 10
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf WZTo1L1Nu2Q_13TeV_amcatnloFXFX 10
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf WZTo1L3Nu_13TeV_amcatnloFXFX 10
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf WZTo2L2Q_13TeV_amcatnloFXFX 10
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf WZJToLLLNu_13TeV_amcatnloFXFX 10
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf DYJetsToLL_M-50_13TeV-madgraphMLM 10
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf ZJetsToNuNu_HT-100To200_13TeV-madgraph 5
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf ZJetsToNuNu_HT-200To400_13TeV-madgraph 5
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf ZJetsToNuNu_HT-400To600_13TeV-madgraph 5
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf ZJetsToNuNu_HT-600To800_13TeV-madgraph 5
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf ZZTo2L2Q_13TeV_amcatnloFXFX 10
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf ZZTo4L_13TeV_powheg 10

./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf WToTauNu_M-200_13TeV-pythia8 2
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf WToMuNu_M-200_13TeV-pythia8 2

./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_jesDown.conf WToTauNu_M-200_13TeV-pythia8_jesDown 2
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_jesUp.conf WToTauNu_M-200_13TeV-pythia8_jesUp 2
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_uesDown.conf WToTauNu_M-200_13TeV-pythia8_uesDown 2
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_uesUp.conf WToTauNu_M-200_13TeV-pythia8_uesUp 2
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_taues_1prong0pizerosDown.conf WToTauNu_M-200_13TeV-pythia8_taues_1prong0pizerosDown 2
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_taues_1prong0pizerosUp.conf WToTauNu_M-200_13TeV-pythia8_taues_1prong0pizerosUp 2
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_taues_1prongUpTo4pizerosDown.conf WToTauNu_M-200_13TeV-pythia8_taues_1prongUpTo4pizerosDown 2
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_taues_1prongUpTo4pizerosUp.conf WToTauNu_M-200_13TeV-pythia8_taues_1prongUpTo4pizerosUp 2
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_taues_3prong0pizerosDown.conf WToTauNu_M-200_13TeV-pythia8_taues_3prong0pizerosDown 2
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_taues_3prong0pizerosUp.conf WToTauNu_M-200_13TeV-pythia8_taues_3prong0pizerosUp 2

./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_jesDown.conf WToMuNu_M-200_13TeV-pythia8_jesDown 2
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_jesUp.conf WToMuNu_M-200_13TeV-pythia8_jesUp 2
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_uesDown.conf WToMuNu_M-200_13TeV-pythia8_uesDown 2
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_uesUp.conf WToMuNu_M-200_13TeV-pythia8_uesUp 2
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_muDown.conf WToMuNu_M-200_13TeV-pythia8_muDown 2
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_muUp.conf WToMuNu_M-200_13TeV-pythia8_muUp 2

# For tauID (including trigger efficiencies + fake rate)
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer.conf MET_Run2016 20



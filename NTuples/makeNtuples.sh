#!bin/sh

# For trigger efficiencies
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer.conf SingleMuon_Run2016 20
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf WJetsToLNu_13TeV-madgraphMLM 5

# For fake rate (no trigger efficiencies need to be included)
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer.conf JetHT_Run2016 20

# For n_EWK (including trigger efficiencies)
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer.conf MET_Run2016 10
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf WJetsToLNu_13TeV-madgraphMLM 10
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf TTJets_13TeV-powheg 10
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf ST_t-channel_top_4f_inclusiveDecays_13TeV-powheg 10
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powheg 10
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf ST_tW_top_5f_inclusiveDecays_13TeV-powheg 10
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg 10
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf VVTo2L2Nu_13TeV_amcatnloFXFX 10
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf WWTo1L1Nu2Q_13TeV_amcatnloFXFX 10
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf WZTo1L1Nu2Q_13TeV_amcatnloFXFX 10
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf WZTo1L3Nu_13TeV_amcatnloFXFX 10
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf WZTo2L2Q_13TeV_amcatnloFXFX 10
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf DYJetsToLL_M-50_13TeV-madgraphMLM 10
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf ZJetsToNuNu_HT-100To200_13TeV-madgraph 10
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf ZJetsToNuNu_HT-200To400_13TeV-madgraph 10
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf ZJetsToNuNu_HT-400To600_13TeV-madgraph 10
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf ZJetsToNuNu_HT-600To800_13TeV-madgraph 10

# For tauID (including trigger efficiencies + fake rate)
./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer.conf MET_Run2016 20

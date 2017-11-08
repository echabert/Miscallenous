
void Extract2D(string filename, string ofilename){
//gExp gExp1m gExp1p gObs gObs1m gObs1p
//TFile* fint = TFile::Open("RootFilesAndTarFiles/CMS-SUS-16-051_Figure_005.root");
TFile* fint = TFile::Open(filename.c_str());
TH2D* h2 = (TH2D*) fint->Get("correlationMatrix");
int nx = h2->GetNbinsX()+1;
int ny = h2->GetNbinsY()+1;

ofstream ofile(ofilename); 

Double_t value = 0;
ofile<<"dependent_variables:"<<endl;
ofile<<"- header: {name: Correlation}"<<endl;
ofile<<"  qualifiers:"<<endl;
ofile<<"  - {name: RE, value: P P --> STOP STOP}"<<endl;
ofile<<"  - {name: SQRT(S), units: GeV, value: '13000.0'}"<<endl;
ofile<<"  values:"<<endl;
//print x
for(int i=0;i<nx;i++){
  for(int j=0;j<ny;j++){
    value = h2->GetBinContent(i,j)/100;
    if(value>0) ofile<<"  - {value: "<<std::setprecision(4)<<value<<"}"<<endl;
  }
}
ofile<<"independent_variables:"<<endl;
ofile<<"- header: {name: 'regions'}"<<endl;
ofile<<"  values:"<<endl;
//print y
for(int i=0;i<nx;i++){
  for(int j=0;j<ny;j++){
    value = h2->GetBinContent(i,j);
    //get BinLabel
    if(value>0) ofile<<"  - {value: "<<h2->GetXaxis()->GetBinLabel(i)<<"}"<<endl;
  }
}
//print value
ofile<<"- header: {name: 'regions'}"<<endl;
ofile<<"  values:"<<endl;
for(int i=0;i<nx;i++){
  for(int j=0;j<ny;j++){
    value = h2->GetBinContent(i,j);
    if(value>0) ofile<<"  - {value: "<<h2->GetXaxis()->GetBinLabel(j)<<"}"<<endl;
  }
}

}



void ExtractCorrelation(){
	Extract2D("RootFilesAndTarFiles/CMS-SUS-16-051_Figure_010.root","Table9.yaml");
	Extract2D("RootFilesAndTarFiles/CMS-SUS-16-051_Figure_011.root","Table10.yaml");
}

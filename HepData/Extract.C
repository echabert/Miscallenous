#include <iostream>
#include <iomanip>
using namespace std;

void ExtractOne(string filename, string ofilename){
//gExp gExp1m gExp1p gObs gObs1m gObs1p
//TFile* fint = TFile::Open("RootFilesAndTarFiles/CMS-SUS-16-051_Figure_005.root");
TFile* fint = TFile::Open(filename.c_str());
TGraph* g = (TGraph*) fint->Get("gObs");
TGraph* g2 = (TGraph*) fint->Get("gObs_2");
int n = g->GetN();
int n2 = g2->GetN();

ofstream ofile(ofilename); 

Double_t x = 0;
Double_t y = 0;
ofile<<"dependent_variables:"<<endl;
ofile<<"- header: {name: '$m_{\\tilde{\\chi}^0_1}$', units: GeV}"<<endl;
ofile<<"  qualifiers:"<<endl;
ofile<<"  - {name: RE, value: P P --> STOP STOP}"<<endl;
ofile<<"  - {name: SQRT(S), units: GeV, value: '13000.0'}"<<endl;
ofile<<"  values:"<<endl;
//print x
for(int i=0;i<n2;i++){
  g2->GetPoint(i,x,y);
  ofile<<"  - {value: "<<std::fixed<<std::setprecision(1)<<y<<"}"<<endl;
}
for(int i=0;i<n;i++){
  g->GetPoint(i,x,y);
  ofile<<"  - {value: "<<std::fixed<<std::setprecision(1)<<y<<"}"<<endl;
}

ofile<<"independent_variables:"<<endl;
ofile<<"- header: {name: '$m_{\\tilde{t}}$', units: GeV}"<<endl;
ofile<<"  values:"<<endl;

//print y
for(int i=0;i<n2;i++){
  g2->GetPoint(i,x,y);
  ofile<<"  - {value: "<<std::fixed<<std::setprecision(1)<<x<<"}"<<endl;
}
for(int i=0;i<n;i++){
  g->GetPoint(i,x,y);
  ofile<<"  - {value: "<<std::fixed<<std::setprecision(1)<<x<<"}"<<endl;
}

}

void Extract2D(string filename, string ofilename){
//gExp gExp1m gExp1p gObs gObs1m gObs1p
//TFile* fint = TFile::Open("RootFilesAndTarFiles/CMS-SUS-16-051_Figure_005.root");
TFile* fint = TFile::Open(filename.c_str());
TH2D* h2 = (TH2D*) fint->Get("hObsXsec");
int nx = h2->GetNbinsX();
int ny = h2->GetNbinsY();

ofstream ofile(ofilename); 

Double_t value = 0;
ofile<<"dependent_variables:"<<endl;
ofile<<"- header: {name: SIG, units: FB}"<<endl;
ofile<<"  qualifiers:"<<endl;
ofile<<"  - {name: RE, value: P P --> STOP STOP}"<<endl;
ofile<<"  - {name: SQRT(S), units: GeV, value: '13000.0'}"<<endl;
ofile<<"  values:"<<endl;
//print x
for(int i=0;i<nx;i++){
  for(int j=0;j<ny;j++){
    value = h2->GetBinContent(i,j);
    if(value>0) ofile<<"  - {value: "<<std::setprecision(4)<<value<<"}"<<endl;
  }
}
ofile<<"independent_variables:"<<endl;
ofile<<"- header: {name: '$m_{\\tilde{t}}$', units: GeV}"<<endl;
ofile<<"  values:"<<endl;
//print y
for(int i=0;i<nx;i++){
  for(int j=0;j<ny;j++){
    value = h2->GetBinContent(i,j);
    if(value>0) ofile<<"  - {value: "<<std::fixed<<std::setprecision(0)<<h2->GetXaxis()->GetBinCenter(i)<<"}"<<endl;
  }
}
cout<<"THERE"<<endl;
//print value
ofile<<"- header: {name: '$m_{\\tilde{\\chi}^0_1}$, units: GeV'}"<<endl;
ofile<<"  values:"<<endl;
for(int i=0;i<nx;i++){
  for(int j=0;j<ny;j++){
    value = h2->GetBinContent(i,j);
    if(value>0) ofile<<"  - {value: "<<std::fixed<<std::setprecision(0)<<h2->GetXaxis()->GetBinCenter(j)<<"}"<<endl;
  }
}

}


void Extract(){

  //ExtractOne("RootFilesAndTarFiles/CMS-SUS-16-051_Figure_005.root","gExp","Table2.yaml");
  //ExtractOne("RootFilesAndTarFiles/CMS-SUS-16-051_Figure_005.root","gExp1m","Table3.yaml");
  //ExtractOne("RootFilesAndTarFiles/CMS-SUS-16-051_Figure_005.root","gExp1p","Table4.yaml");
  cout<<"A"<<endl;
  ExtractOne("RootFilesAndTarFiles/CMS-SUS-16-051_Figure_005.root","Table3.yaml");
  cout<<"A"<<endl;
  Extract2D("RootFilesAndTarFiles/CMS-SUS-16-051_Figure_005.root","Table4.yaml");
  //ExtractOne("RootFilesAndTarFiles/CMS-SUS-16-051_Figure_005.root","gObs1m","Table6.yaml");
  //ExtractOne("RootFilesAndTarFiles/CMS-SUS-16-051_Figure_005.root","gObs1p","Table7.yaml");
  cout<<"A"<<endl;
  ExtractOne("RootFilesAndTarFiles/CMS-SUS-16-051_Figure_006.root","Table5.yaml");
  cout<<"A"<<endl;
  Extract2D("RootFilesAndTarFiles/CMS-SUS-16-051_Figure_006.root","Table6.yaml");
  ExtractOne("RootFilesAndTarFiles/CMS-SUS-16-051_Figure_007.root","Table7.yaml");
  Extract2D("RootFilesAndTarFiles/CMS-SUS-16-051_Figure_007.root","Table8.yaml");

}

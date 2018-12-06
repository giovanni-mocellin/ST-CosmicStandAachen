#include "DataStructures.h"
#include "KascadeChannelMap.h"
#include <Riostream.h>
#include <iomanip>
#include <string.h>
#include <vector>
#include <iostream>
#include <fstream>
#include "TH1.h"
#include "TH2D.h"
#include "TH2.h"
#include "TH3F.h"
#include "TF1.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TLatex.h"
#include <iostream>
#include <cstdlib>
#include <limits>
#include <algorithm>
#include "TGraphErrors.h"

bool debug = false;

using namespace std;

void Reco_Plots()
{
    float x_hits[3];
    float x_err[3] = {1,1,1}; // cm
    TH1F *h_chi2_x = new TH1F("h_chi2_x","",20,0,10);
    TH1F *h_m_x = new TH1F("h_m_x","",80,-2,2);
    TH1F *h_q_x = new TH1F("h_q_x","",200,0,200);
    
    float y_hits[3];
    float y_err[3] = {1,1,1}; // cm
    TH1F *h_chi2_y = new TH1F("histo_chi2_y","",20,0,10);
    TH1F *h_m_y = new TH1F("h_m_y","",80,-2,2);
    TH1F *h_q_y = new TH1F("h_q_y","",384,0,384);
    
    DStrip d_hits[3];
    bool d_confirmed[3];
    
    float z_hits[3];
    float z_err[3] = {0,0,0}; // cm
    
    TH2F *occu[3];
    char *histname = new char[10];
    for (int lay=0; lay<3; lay++)
    {
        sprintf(histname,"h_occu_%u",lay+1);
        occu[lay] = new TH2F(histname,"",200,0,200,384,0,384);
    }
    
    ifstream in;
    in.open("RefinedDataPoints.txt");
    
    while (!in.eof())
    {
        for (int lay=0; lay<3; lay++)
        {
            in >> x_hits[lay];
            in >> y_hits[lay];
            in >> z_hits[lay];
            in >> d_hits[lay].m;
            in >> d_hits[lay].q;
            in >> d_confirmed[lay];
            occu[lay]->Fill(x_hits[lay],y_hits[lay]);
        }
        
        TGraphErrors *gr_x = new TGraphErrors(3,z_hits,x_hits,z_err,x_err);
        TF1 *f1 = new TF1("f1","pol1",-5000,5000);
        gr_x->Fit("f1","Q");
        h_chi2_x->Fill(f1->GetChisquare());
        if (f1->GetChisquare() > 3) continue;
        h_q_x->Fill(f1->GetParameter(0));
        h_m_x->Fill(f1->GetParameter(1));
        
        TGraphErrors *gr_y = new TGraphErrors(3,z_hits,y_hits,z_err,y_err);
        TF1 *f2 = new TF1("f2","pol1",-5000,5000);
        gr_y->Fit("f2","Q");
        h_chi2_y->Fill(f2->GetChisquare());
        if (f2->GetChisquare() > 3) continue;
        h_q_y->Fill(f2->GetParameter(0));
        h_m_y->Fill(f2->GetParameter(1));
    }
    
    in.close();
    
    TCanvas *cnv_occupancy = new TCanvas("cnv_occupancy", "cnv_occupancy",0,0,1600,700);
    cnv_occupancy->Divide(3);
    for (int lay=0; lay<3; lay++)
    {
        cnv_occupancy->cd(lay+1);
        occu[lay]->Draw();
    }
    
    TCanvas *cnv_tracks_x = new TCanvas("cnv_tracks_x", "cnv_tracks_x",0,0,1600,700);
    cnv_tracks_x->Divide(3);
    cnv_tracks_x->cd(1);
    h_m_x->GetXaxis()->SetTitle("Angle in x-z plane [rad]");
    h_m_x->GetYaxis()->SetTitle("Counts");
    h_m_x->Draw();
    cnv_tracks_x->cd(2);
    h_q_x->SetMinimum(0);
    h_q_x->GetXaxis()->SetTitle("Extrap on 1st layer x [cm]");
    h_q_x->GetYaxis()->SetTitle("Counts");
    h_q_x->Draw();
    cnv_tracks_x->cd(3);
    h_chi2_x->GetXaxis()->SetTitle("#chi^2");
    h_chi2_x->GetYaxis()->SetTitle("Counts");
    h_chi2_x->Draw();
    
    TCanvas *cnv_tracks_y = new TCanvas("cnv_tracks_y", "cnv_tracks_y",0,0,1600,700);
    cnv_tracks_y->Divide(3);
    cnv_tracks_y->cd(1);
    h_m_y->GetXaxis()->SetTitle("Angle in y-z plane [rad]");
    h_m_y->GetYaxis()->SetTitle("Counts");
    h_m_y->Draw();
    cnv_tracks_y->cd(2);
    h_q_y->SetMinimum(0);
    h_q_y->GetXaxis()->SetTitle("Extrap on 1st layer y [cm]");
    h_q_y->GetYaxis()->SetTitle("Counts");
    h_q_y->Draw();
    cnv_tracks_y->cd(3);
    h_chi2_y->GetXaxis()->SetTitle("#chi^2");
    h_chi2_y->GetYaxis()->SetTitle("Counts");
    h_chi2_y->Draw();
}


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

using namespace std;

void RawDataSorting(string infile)
{
    string indata;
    string delimiter = ";";
    size_t pos = 0;
    
    float time = 0;
    bool timeflag;
    int i;
    float hit;
    
    float x_hits[3][2];
    float y_hits[3][2];
    DStrip d_hits[3][3];
    float z_hits[3] = {0,82,164}; // cm
    
    point3D hit3D[3];
    
    bool Matched = false;
    TH1F *h_matched[3];
    char *histname = new char[10];
    for (int i=0; i<3; i++)
    {
        sprintf(histname,"h_matched_%u",i+1);
        h_matched[i] = new TH1F(histname,"",2,0,2);
    }
    
    TH1F *dist[3];
    for (int i=0; i<3; i++)
    {
        sprintf(histname,"h_dist_%u",i+1);
        dist[i] = new TH1F(histname,"",160,-40,40);
    }
    
    ifstream in;
    in.open(infile);
    
    ofstream out;
    out.open("RefinedDataPoints.txt");
    
    while (!in.eof())
    {
        for (int lay=0; lay<3; lay++)
        {
            for (int multiplicity=0; multiplicity<3; multiplicity++)
            {
                x_hits[lay][multiplicity] = 999999.0;
                y_hits[lay][multiplicity] = 999999.0;
                d_hits[lay][multiplicity].m = 999999.0;
                d_hits[lay][multiplicity].q = 999999.0;
            }
            hit3D[lay].x = hit3D[lay].y = hit3D[lay].d.m = hit3D[lay].d.q = hit3D[lay].z = 999999.0;
        }
        
        getline(in,indata);
        timeflag = true;
        i = 0;
        
        while ((pos = indata.find(delimiter)) != string::npos)
        {
            if (timeflag)
            {
                time = stof(indata.substr(0, pos));
                indata.erase(0, pos + delimiter.length());
                timeflag = false;
                continue;
            }
            if (!timeflag)
            {
                hit = stof(indata.substr(0, pos));
                
                if (hit>0 && hit<=32) {
                    for (int p=0; p<2; p++) {
                        if (x_hits[0][p] == 999999.0) {
                            x_hits[0][p] = WirePos(float(hit+32),'A');  // Layer 1 => Type 1
                            break;
                        }}}
                
                if (hit>96 && hit<=128) {
                    for (int p=0; p<2; p++) {
                        if (x_hits[1][p] == 999999.0) {
                            x_hits[1][p] = WirePos(float(hit-64),'B');  // Layer 2 => Type 2
                            break;
                        }}}
                
                if (hit>192 && hit<=224) {
                    for (int p=0; p<2; p++) {
                        if (x_hits[2][p] == 999999.0) {
                            x_hits[2][p] = WirePos(float(hit-160),'A'); // Layer 3 => Type 1
                            break;
                        }}}
                
                if (hit>32 && hit<=64) {
                    for (int p=0; p<2; p++) {
                        if (y_hits[0][p] == 999999.0) {
                            y_hits[0][p] = HStripPos(float(hit+32),'A');  // Layer 1 => Type 1
                            break;
                        }}}
                
                if (hit>128 && hit<=160) {
                    for (int p=0; p<2; p++) {
                        if (y_hits[1][p] == 999999.0) {
                            y_hits[1][p] = HStripPos(float(hit-64),'B');  // Layer 2 => Type 2
                            continue;
                        }}}
                
                if (hit>224 && hit<=256) {
                    for (int p=0; p<2; p++) {
                        if (y_hits[2][p] == 999999.0) {
                            y_hits[2][p] = HStripPos(float(hit-160),'A'); // Layer 3 => Type 1
                            break;
                        }}}
                
                if (hit>64 && hit<=96) {
                    for (int p=0; p<3; p++) {
                        if (d_hits[0][p].m == 999999.0) {
                            d_hits[0][p] = DStripPos(float(hit-32),'A');  // Layer 1 => Type 1
                            break;
                        }}}
                
                if (hit>160 && hit<=192) {
                    for (int p=0; p<3; p++) {
                        if (d_hits[1][p].m == 999999.0) {
                            d_hits[1][p] = DStripPos(float(hit-128),'B'); // Layer 2 => Type 2
                            break;
                        }}}
                
                if (hit>256 && hit<=288) {
                    for (int p=0; p<3; p++) {
                        if (d_hits[2][p].m == 999999.0) {
                            d_hits[2][p] = DStripPos(float(hit-224),'A'); // Layer 3 => Type 1
                            break;
                        }}}
                
                indata.erase(0, pos + delimiter.length());
                i++;
            }
        }
        
        for (int lay=0; lay<3; lay++)
        {
            if (x_hits[lay][0] != 999999.0 && x_hits[lay][1] == 999999.0) hit3D[lay].x = x_hits[lay][0];
            if (x_hits[lay][0] != 999999.0 && x_hits[lay][1] != 999999.0 && fabs( x_hits[lay][0] - x_hits[lay][1] ) < 3) hit3D[lay].x = (x_hits[lay][0]+x_hits[lay][1])/2;
            
            if (y_hits[lay][0] != 999999.0 && y_hits[lay][1] == 999999.0) hit3D[lay].y = y_hits[lay][0];
            if (y_hits[lay][0] != 999999.0 && y_hits[lay][1] != 999999.0 && fabs( y_hits[lay][0] - y_hits[lay][1] ) < 3) hit3D[lay].y = (y_hits[lay][0]+y_hits[lay][1])/2;
            
            if (d_hits[lay][0].q != 999999.0 && d_hits[lay][1].q == 999999.0 && d_hits[lay][2].q == 999999.0) {
                hit3D[lay].d.m = d_hits[lay][0].m;
                hit3D[lay].d.q = d_hits[lay][0].q; }
            if (d_hits[lay][0].q != 999999.0 && d_hits[lay][1].q != 999999.0 && d_hits[lay][2].q == 999999.0 && fabs(d_hits[lay][1].q - d_hits[lay][0].q) < 6) {
                hit3D[lay].d.m = d_hits[lay][0].m;
                hit3D[lay].d.q = (d_hits[lay][0].q+d_hits[lay][1].q)/2; }
            if (d_hits[lay][0].q != 999999.0 && d_hits[lay][1].q != 999999.0 && d_hits[lay][2].q != 999999.0 && fabs(d_hits[lay][2].q - d_hits[lay][0].q) < 10) {
                hit3D[lay].d.m = d_hits[lay][0].m;
                hit3D[lay].d.q = d_hits[lay][1].q; }
        }
        
        hit3D[0].z = 0;
        hit3D[1].z = 82;
        hit3D[2].z = 164;
        
        for (int lay=0; lay<3; lay++)
        {
            if (hit3D[0].x == 999999.0 || hit3D[0].y == 999999.0 || hit3D[1].x == 999999.0 || hit3D[1].y == 999999.0 || hit3D[2].x == 999999.0 || hit3D[2].y == 999999.0) continue;
            
            out << hit3D[lay].x << " " << hit3D[lay].y << " " << hit3D[lay].z << " " << hit3D[lay].d.m << " " << hit3D[lay].d.q;
            
            Matched = false;
            
            float distance = (hit3D[lay].y-(hit3D[lay].d.m*hit3D[lay].x+hit3D[lay].d.q))/sqrt(1+hit3D[lay].d.m*hit3D[lay].d.m);
            dist[lay]->Fill(distance);
            
            if ( fabs(distance) <= 10 && hit3D[lay].d.m != 999999.0 && hit3D[lay].d.q != 999999.0 )
            {
                Matched = true;
            }
            if (Matched == true) out << " 1" << endl;
            if (Matched == false) out << " 0" << endl;
            
            h_matched[lay]->Fill(Matched);
        }
    }
    in.close();
    out.close();
    
    TCanvas *cnv_matched_hits = new TCanvas("cnv_matched_hits", "cnv_matched_hits",0,0,1600,700);
    cnv_matched_hits->Divide(3);
    for (int lay=0; lay<3; lay++)
    {
        cnv_matched_hits->cd(lay+1);
        h_matched[lay]->GetXaxis()->SetTitle("Layer 1: Hit matched?");
        h_matched[lay]->GetYaxis()->SetTitle("Counts");
        h_matched[lay]->Draw();
    }
    
    TCanvas *cnv_dist = new TCanvas("cnv_dist", "cnv_dist",0,0,1600,700);
    cnv_dist->Divide(3);
    for (int lay=0; lay<3; lay++)
    {
        cnv_dist->cd(lay+1);
        dist[lay]->Draw();
    }
}

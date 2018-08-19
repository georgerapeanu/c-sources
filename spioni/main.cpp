#include <fstream>
#include <iostream>
#include <cstring>
using namespace std;
ifstream f("spioni.in");
ofstream g("spioni.out");
char v[5000];
void program(int low, int high, char vec[])
{
    if(low<high)
    {
    int i=0,j=0,med=(low+high)/2;
    char v1[2500]={'\0'},v2[2500]={'\0'};
    for(i=0;i<=high-low+1;i+=2)
    {v1[j]=vec[i];v2[j++]=vec[i+1];}
    program(low,med,v1);
    program(med+1,high,v2);
    }
    else
    {
        v[low]=vec[0];
    }
}
int main()
{
    f.getline(v,5000);
    f.getline(v,5000);
    program(0,strlen(v)-1,v);
    g<<v;
    cout<<strlen("A-,nt.daae.or.i.ree.air.rsindldctcaea.sa.lsbc..n.tall.caau.a-..rni.rohpoj.ai.ee..ea...eeud..esmre.npro.-on.pan.suatl..spdu..manetpnb.mr.n.vdtliraIjea.dieeede.icmlriah.asaeu.rclae.aopllni.a.ieta.u.tafitlts.i.leu.dielroccee.rn.eae..pda.uer.ah.r.bbivlls.aaaia..iptsps.i,..ao..e.p.aeatunenua.llmorofnrntsdcijeci.ai-.ia.a.ainc.beadaec.t-usctu.meragnu.-ua..ar..,oeum.rl.a.ie.spne.eciac.nnp.o.-aaaiere.tci.utap,aat.tuap..ae.nculf.anpcouah,.,dai.i.j-eti,saeeeeaeisictut.sbu.etpua...rlnc.paastnaslclncaisa,dlaoruani..uam.csl-ni-ae.i.ra.aaa,elds,li.icarar.,.is-nrD,n.tasettacai-iinsaaaialeil.r..n.si-adalnpa..t.ieeupniiaccraueIea.iaanea..te.silana.lpneuciafpra..eimAeiietstapm.atc.ia.oreea.nai.sihz;ui..i.am.odsu.seasrc..pfsaafdlnccu.o..ca.la.tas.d.na.inae-t.eiaiau.eiimrdp,.iio...asutstt.aareeatsrcis.eedcue..e.tiaedijee.ceia-ia.asnaaccru.iu.vs...eM.silcelefcs.efain.d..iltcoasiaaricca.ucbaar..o-.r.imadenrmdi.aaiaatleeiu.etcliisipus.s.if.aaipsimn.t.ieaall.evegreiestearmz.i.ei.olcnrla,es.r.trdieailai..ml.m-mincsiaaa.tngeevuuoea.depuim.ac.s.trimasaostateasi.o.idn;.ccsems.v.i.tou.uta..u.a.mai.ammcti.tantorseud.nmbeelapis;eeaanmmnr...a...itopa...siaar..eiancm,.aziiiee.izc.map.,naieriialaarllisimencl.etoubl.asuatic..s.ed.s,tatnulsiicn.ieave.lsaic.arlcpu.rrutd.st.isrotaalemAia,r.Vleitl..ruuti.tvuicue.iuaoiaielt..:fz..aacn.tie.l.-n.s.nd.an...aaau..a.ara,eess.ne..o.l.,iibis..elissicc,uegmmsre,afdaaau.t-dosnpd...pietei.u..e.uoat.u.turptaralltrtui.ne.bm,i..aipeslomm.oeeenrc.adta.ililaa..n.if.D.nusfr.eiIaae.ipu.asnm.o..ome.p..accmna.t..suedvnDcusrp;udeMoal.oct.soi..Siipt.u.oielopuid.ruai.d..tltl.sl.sl.t.ab,ibt.a.ueej...asaia.maaaass.arebmorl.atarccsaepediemita,imucprenrssmcaaecaaiuslba.itil.sr.aizlasej,,cataar.a..rotp,iaaHdrDtcote....z.icrae..aopaal.c,ausd-.ttltim.Pigiiefsm,ai,.re,lgt.ae-sse.etdauginme.ia.ec.H.!..as,ue.-p.aeoae.mfdt.apdue.ldmtd..auev.rmiaaevu.reialcrottpabaraa.asgceaaui..r!tsltia,c..ti.ae.iraometasamrd..iace.;.mi..aaiet..t.ns..isei.aiaaedm.elnmeca,.aa.vcaddoa.etrcd..:la.iscarn;ucgusb.lmu,.e.s.tilinairal.s.t.me.eruats.lcaotuea,c.ms.ueoe.iscrus.i-ascnmeaai-ei.ieias.ro.iaetaatpdnumaenaru.hromi..nzeaiealf-np.,iirrdaz...ecm.ta..ioeecTiiesatetili.ubcpaegslar.aaoeunagdiceui..aiau..dan...o.d.aa.a.taa.etprneuar.itareaiaasat.e.clir.o.tuectms.lla....adaas.re.e.p.o.oedeap.orafu.uotoa.utsr..ieevuiiu.M..bpusatpaitm.nine..iim..icarisiuaueenuru.a,nlr.pcia.ecala.l..aadeonaa:lsarg.aases..na.ect.c..ivbta.cn.niuu.s.am.ioa.rc.nssi,ila.praernada.ltaiu--a.nt,ugam.ic,iih.t.e.i.eplsniual...crc..arvsi.aa.e.iole.uerm.czmecad,r.iae.ieiota.si..eu.zsn,u.ddn.i.ipooeia.t.smi,p.l,..uea.ucseacepad.nmasaaa.cteniaoupei.A..eirrr.in.neculdtainiruru-e.flovn.,cac...ioam--a.s..t.crrdouscicuti.ptat..u.trre.cp..elpn.suau.aat.aujevare..svtpnceeev.mtstn.np.seeltiitaaacsart,toi.erelsipra.l,lau.tie..rcvd..aefncvosma.ntideo.D,naocD.a..tias.pa,.,eaar.eDtlu.acvblde...an...be,jnie.oitdn.uaump.iariapu.uatlau..rretc.lnnipegd.aeamse.r.eiau,unuevintrmapad.p.ujuaae.nrin..ear.ng.a,aauei,r.ices.rdrn.et.aim.ciitrtaare.rears...iieimnf..maiec.el..aeelea.,.inu..igaapua.iieemir.n.au,.emna.cda.a..il.hn-feaeusic.cetu..aunip.rt.ciai..aiu.tiean.m.nsamapeai.pcparasdertacui.teiapu..tcene.rlpmaaacoaertd.d.aroviVmian.e.n...eau.ite.c..stciepar-d.gcs..cmrabsaau.esalieei..s.u.itcb,ecipiaf.ema.rp.d.atm.eic.j-e.atepnuateu.epsaanaimiructeaimtpcocei.bae..eeuspa,le.nuelnan.dtdra.t.naaff.aidaicuasec.vesttatmgepsimaimt..flusle..i:ei.d.mpsduc...,nuds.,.eecea...aao-ar..le....meielidaeailam.a..sldt.lna..cgmarai.cu.u.aai.cs.,mla.nsa.ioatidpusi..l.aemcuopmouna.,dsus.aiaacitaavananrlm.ucste.pa.naro.armcpiaievd.nccc-eatuant.o..u.ariesneani.,otf..urilciuaura..ip.i..a.aV.ueedabtcemecso.marsncm.,uica.it..carnrzaan.a,eameotna.aeuit,lpe...ter..eniai.a-aavrts.urtaste.rPmelbseantmi;rtau..e.adloo.psgrie..r:aaee.are.ifdtntnrat.snrso.iapu.dgaeaaeu.empsunic..eoi.r..li..trosz.sii.s.ea.ma,ueaa,.A.usam.adii.mldtodtnn.acarias.orcato.predt.p.eveoisrsenment.seaseeriutbtntruui..scnauePetaam..ilnoij.afcezn..unaroeimu.,apc.tinsmurttiCcaoitsnniina.atr..al.ideial.o.tmieueea.f,eaeib..erceuriei.rueieap.ii.Hrnimr;aats.emsvic.seja.emcetdahitenei.ea");
   return 0;
}

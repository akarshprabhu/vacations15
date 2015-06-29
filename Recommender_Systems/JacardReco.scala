//Script implementing recommender system to the given data set using Jacard's Similarity'
//Using Scala

import io.Source
import scala.util.control.Breaks._
var s = Source.fromFile("u.data")
var t = s.mkString.split("\\s+")
var r = for(w<-t) yield w.toInt
var rat =Array.ofDim[Int](944,1683)
var inter = Array.ofDim[Int](943)
var uni = Array.ofDim[Int](943)
var sim = Array.ofDim[Double](943)
var m=700
var best = Array.ofDim[Int](50)
var movie = Array.ofDim[Int](1683)
var bestR = Array.ofDim[Int](50)
var bestM = Array.ofDim[Int](50)
for(i <- 0 to r.size/4-1){
 var k=i*4;
rat(r(k))(r(k+1))=r(k+2)
}

/*for(i<- 0 to 942 ; j<- 0 to 1682){
if(rat(i)(j)!=0){
println(i+"\t"+j+"\t"+rat(i)(j))
}
}*/


val row = 942
val col = 1681


for(i<-0 to row){
	breakable{
		for(j<-0 to col){
			if(i==m) break
			if((rat(m)(j)-rat(i)(j))<2&&rat(m)(j)!=0&&rat(i)(j)!=0){
			 inter(i)+=1 //calculating intersection count
		    }
			if(!(rat(m)(j)==0&&rat(i)(j)==0)){uni(i)+=1} //calculating union count
		}
		sim(i)=(inter(i)*1.0)/(uni(i)*1.0) //calculating jacards similarity for each user pair
		
	}
}

//for(i<- 0 to sim.size-1) println(sim(i))

var m1=sim.indexOf(sim.max)
sim(m1)=0
var m2=sim.indexOf(sim.max) //finds 2 ppl most similar to the reqd person





//best 50 movies
for(i<-0 to col){
	for(j<-0 to row){
		if(rat(j)(i)!=0) movie(i)+=1
	}
} 

for(i<-0 to 49){
	var x = movie.indexOf(movie.max)
	movie(x)=0
	best(i)=x //has the 50 most watched movies
	//print(best(i)+" ")
}

for(i<- 0 to 49 ){
	for(j<- 0 to row-1){
		if(rat(j)(best(i))==5){
			bestR(i)+=1 // sorts w.r.t max 5 ratings
		}
	}
}

for(i <- 0 to bestR.size-1 ){
	//print(bestR(i) + " ")
}

for(i<-0 to bestR.size-1){
	var y = bestR.indexOf(bestR.max)
	bestR(y)=0
	bestM(i)=best(y)
	//print(bestM(i)+"\n") // has the top 50 movies
}

var con=0
breakable{


//recommendations case 1
for(i<-0 to row){
 	if(rat(m)(i)==0&&(rat(m1)(i)==5||rat(m2)(i)==5)&&best.contains(i)){ // selects 3 from already made recommendations list w.r.t top 50 list
 		if((rat(m1)(i)>rat(m2)(i))&&rat(m1)(i)>2){
 			println("Movie recommended "+(i+1)+ " it has been rated "+rat(m1)(i)+" by similar people")
 			con+=1
 		}
 		else{
 			if(rat(m2)(i) >2&&best.contains(i)){
 				println("Movie recommended "+(i+1)+ " it has been rated "+rat(m2)(i)+" by similar people")
 				con+=1
 			}
 		}
 		} 
 		if(con>2) break
 	}
// case 2 if the recommended movies isnt in the top 50 list	
 	if(con<3){
 		
 		for(i<-0 to row){
 	if(rat(m)(i)==0&&(rat(m1)(i)==5||rat(m2)(i)==5)){
 		if((rat(m1)(i)>rat(m2)(i))&&rat(m1)(i)>2){
 			println("Movie recommended "+(i+1)+ " it has been rated "+rat(m1)(i)+" by similar people")
 			con+=1
 		}
 		else{
 			if(rat(m2)(i) >2){
 				println("Movie recommended "+(i+1)+ " it has been rated "+rat(m2)(i)+" by similar people")
 				con+=1
 			}
 		}
 		} 
 		if(con>2) break
 	}
 	
 }
// case 3 if the person is not similar at all
 if(con<3){
 	var k=0
 	for(i<-con to 3){
 		println("Movie recommended "+ bestM(k))
 		k+=1
 		if(con>2)break
 	}
 	
 }
 	
}

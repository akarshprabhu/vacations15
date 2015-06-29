//Script implementing recommender system to the given data set using Cosine Distance with normalization w.r.t. user
//Using Scala

import io.Source
import math._
import scala.util.control.Breaks._


var s = Source.fromFile("u.data")
var t = s.mkString.split("\\s+")
var r = for(w<-t) yield w.toInt


var rat =Array.ofDim[Double](944,1683)
var norm = Array.ofDim[Double](944,1683)
var y=0
var names = Array.ofDim[String](1683)

print("Enter your ID: ")
val m = readInt

for(line <- Source.fromFile("u.item").getLines())
{
 names(y) = line
 y = y + 1
}

var sim = Array.ofDim[Double](944)




var best = Array.ofDim[Int](51)
var movie = Array.ofDim[Int](1683)
var bestR = Array.ofDim[Int](51)
var bestM = Array.ofDim[Int](51)
var nn=50 //no of top
for(i <- 0 to r.size/4-1){
 var k=i*4;
rat(r(k))(r(k+1))=r(k+2)
}

/*for(i<- 0 to 4 ; j<- 0 to 7){
if(rat(i)(j)!=0){
println(i+"\t"+j+"\t"+rat(i)(j))
}
}*/

val row = 943
val col = 1682
var ct=0
var su = 0.0
var av = 0.0
for(i<-0 to row)
{
	su=0
	av=0
	ct=0

		for(j<-0 to col)
		{
			
				if(rat(i)(j)!=0)
				{
					su+=rat(i)(j)
					ct+=1
				}
				
		}
		av=su/ct
		
		for(j<-0 to col)
		{
			
			if(rat(i)(j)!=0)
			{
				norm(i)(j)=rat(i)(j)-av
			}
		}
	
}


for(i<-1 to row)
{
	var d1=0.0
	var d2=0.0
	breakable{
	for(j<-0 to col)
	{	
		if(i==m)
		break
		
		if(norm(i)(j)!=0&&norm(m)(j)!=0){
			sim(i)+=norm(m)(j)*norm(i)(j)
		}
		d1 += norm(i)(j)*norm(i)(j)
		d2 += norm(m)(j)*norm(m)(j)
	}
		if((sqrt(d1)*sqrt(d2))	!=0){
		sim(i) /= (sqrt(d1)*sqrt(d2))
		}	
}}		

//for(i<- 1 to sim.size-1) println(sim(i))

var m1=sim.indexOf(sim.max)
sim(m1)= -9999
var m2=sim.indexOf(sim.max) //finds 2 ppl most similar to the reqd person





//best 50 movies
for(i<-0 to col-1){
	for(j<-0 to row-1){
		if(rat(j)(i)!=0) movie(i)+=1
	}
} 

for(i<-0 to nn){
	var x = movie.indexOf(movie.max)
	movie(x)=0
	best(i)=x //has the 50 most watched movies
	//print(best(i)+" ")
}

for(i<- 0 to nn ){
	for(j<- 0 to row-1){
		if(rat(j)(best(i))==5){
			bestR(i)+=1 // sorts w.r.t max 5 ratings
		}
	}
}

for(i <- 0 to nn ){
	//print(bestR(i) + " ")
}

for(i<-0 to nn){
	var y = bestR.indexOf(bestR.max)
	bestR(y)=0
	bestM(i)=best(y)
	//print(bestM(i)+"\n") // has the top 50 movies
}

var con=0
breakable{


//recommendations case 1
for(i<-1 to row){
 	if(rat(m)(i)==0&&(rat(m1)(i)>4||rat(m2)(i)>4)&&best.contains(i)){ // selects 3 from already made recommendations list w.r.t top 50 list
 			
 		if((rat(m1)(i)>rat(m2)(i))){
 			println("Movie recommended "+names(i-1)+ " it has been rated "+rat(m1)(i)+" by similar people")
 			con+=1
 		}
 		else{
 			
 				println("Movie recommended "+names(i-1)+ " it has been rated "+rat(m2)(i)+" by similar people")
 				con+=1
 			
 		}
 	}
 		 
 		if(con>2) break
 	}
// case 2 if the recommended movies isnt in the top 50 list	
 	if(con<3){
 		
 		for(i<-1 to row){
 	if(rat(m)(i)==0&&(rat(m1)(i)>4||rat(m2)(i)>4)){
 		if((rat(m1)(i)>rat(m2)(i))&&rat(m1)(i)>2){
 			println("Movie recommended "+names(i-1)+ " it has been rated "+rat(m1)(i)+" by similar people")
 			con+=1
 		}
 		else{
 			if(rat(m2)(i) >2){
 				println("Movie recommended "+names(i-1)+ " it has been rated "+rat(m2)(i)+" by similar people")
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
 	for(i<-con to 2){
 		println("Movie recommended "+ names(bestM(k)-1))
 		k+=1
 		if(con>2)break
 	}
 	
 }
 	
}

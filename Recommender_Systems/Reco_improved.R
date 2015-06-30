##Program implementing recommender system using recommenderlab package
##Further K-means clustering used to reduce RMSE significantly
##Data set used is libimseti.cz dating site, reduced to 1k entries

#function to plot sum of squares for the no. of clusters
wssplot <- function(data, nc=10, seed=1234){
  wss <- (nrow(data)-1)*sum(apply(data,2,var))
  for (i in 2:nc){
    set.seed(seed)
    wss[i] <- sum(kmeans(data, centers=i)$withinss)}
  plot(1:nc, wss, type="b", xlab="Number of Clusters",
       ylab="Within groups sum of squares")}

rati <- read.csv("~/R/rati")
data(rati) 
#loads dataset
head(rati)

df <- scale(rati[-2])   
# -2 as index if you want clusters w.r.t. users(uid), -1 w.r.t items(profile ID)
wssplot(df)


library(NbClust)
set.seed(1234)

#this package function calculates the optimal no. of clusters reqd
nc <- NbClust(df, min.nc=2, max.nc=10, method="kmeans")
table(nc$Best.n[1,])
barplot(table(nc$Best.n[1,]),
        xlab="Numer of Clusters", ylab="Number of Criteria",
        main="Number of Clusters Chosen by 26 Criteria")

set.seed(1234)

#makes optimal no. of clusters
fit.km <- kmeans(df, 4, nstart=25)                          


#listing cluster heads
aggregate(rati[1], by=list(cluster=fit.km$cluster), mean)


#gives recommendation
library(recommenderlab)
rati.data <- read.csv("~/R/rati.data")
rati.mat<- as(rati.data,"realRatingMatrix")

#makes matrices using the clusters
mat1<-as(fit.km$centers,"realRatingMatrix") 

#the chosen recommender model
Rec.model<-Recommender(rati.mat[1:702], method = "RANDOM") 
recommended.items.u <- predict(Rec.model, rati.mat["700",], n=5)
as(recommended.items.u, "list")  #prints recommendations

#evaluation of 2 recommender models

e <- evaluationScheme(mat1[1:4], method="split", train=0.8, given=1)
Rec.pop <- Recommender(getData(e, "train"), "POPULAR")
Rec.ran <- Recommender(getData(e, "train"), "RANDOM")

#predictions with the corresponding models
p.pop <- predict(Rec.pop, getData(e, "known"), type="ratings")
p.ran <- predict(Rec.ran, getData(e, "known"), type="ratings")

#error calculations with the corresponding models for this dataset
error.pop<-calcPredictionAccuracy(p.pop, getData(e, "unknown"))
error.ran<-calcPredictionAccuracy(p.ran, getData(e, "unknown"))
error <- rbind(error.pop,error.ran)
rownames(error) <- c("POPULAR","RANDOM")
error


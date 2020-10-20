Sys.setlocale("LC_TIME", "English")

library(quantmod)
apple <- getSymbols("AAPL", from = "2019-06-30", to = "2019-12-31", auto.assign = F)
nintendo <- getSymbols("NTDOY", from = "2019-06-30", to = "2019-12-31", auto.assign = F)
facebook <- getSymbols("FB", from = "2019-06-30", to = "2019-12-31", auto.assign = F)
macdonald <- getSymbols("MCDMF", from = "2019-06-30", to = "2019-12-31", auto.assign = F)
BOA <- getSymbols("BAC", from = "2019-06-30", to = "2019-12-31", auto.assign = F)


apple <- as.data.frame(apple)
nintendo <- as.data.frame(nintendo)
facebook <- as.data.frame(facebook)
macdonald <- as.data.frame(macdonald)
BOA  <- as.data.frame(BOA)




write.table(apple, "E:\\Stevens\\2020-SPRING\\FE-522\\homework1\\Q6\\input\\apple.csv", sep = " ", col.names = F)
write.table(nintendo, "E:\\Stevens\\2020-SPRING\\FE-522\\homework1\\Q6\\input\\nintendo.csv", sep = " ", col.names = F)
write.table(facebook, "E:\\Stevens\\2020-SPRING\\FE-522\\homework1\\Q6\\input\\facebook.csv", sep = " ", col.names = F)
write.table(macdonald, "E:\\Stevens\\2020-SPRING\\FE-522\\homework1\\Q6\\input\\macdonald.csv", sep = " ",  col.names = F)
write.table(BOA, "E:\\Stevens\\2020-SPRING\\FE-522\\homework1\\Q6\\input\\BOA.csv", sep = " ", col.names = F)



portfolio_value <- read.csv("E:\\Stevens\\2020-SPRING\\FE-522\\homework1\\output\\Q6Output.csv")
date <- as.Date(portfolio_value[, 1])
plot(date, as.numeric(portfolio_value[,2]), type = "l", main = "Change of portfoloi value", ylab = "Value", xlab = "Date")

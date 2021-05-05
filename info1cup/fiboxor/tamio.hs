import Control.Monad
import Data.Bits
import Data.Array.Unboxed
import Data.List
import qualified Data.ByteString as B

maxk = 20

modulus = 2^maxk

step (x, y)
    | x == 0 && y == 1 = Nothing
    | otherwise = Just (x, (y, (x + y) `mod` modulus))

fibo = 0:unfoldr step (1, 1)

len = length fibo

arr = (listArray (0, len) . scanl xor 0 $ fibo) :: UArray Int Int

pref x = ((x `div` len) `mod` 2) * arr!len `xor` arr!(x `mod` len)

solve x y = pref (y + 1) `xor` pref x

p2 = listArray (1,20) [2^i | i <- [1..20]] :: UArray Int Int

main = do
    cs <- getContents
    let qs = tail $ lines cs
    forM_ qs $ \l -> do
        let [k, x, y] = map (read :: String -> Int) . words $ l
        print $ solve x y `mod` p2!k

import Data.Bits
import Data.IORef
import Control.Monad
import Data.List.Split
import Debug.Trace
import Data.Maybe
import Text.Read

atLeastTwoAndEqual :: [Int] -> Bool
atLeastTwoAndEqual ls = length ls >= 2 && all (==(head ls)) ls

pr x = trace (show x) $ x

isOk :: [Char] -> Bool
isOk = fromMaybe False . fmap atLeastTwoAndEqual . fmap (map (foldr xor 0)) . sequence . map sequence . map (map readMaybe) . map (splitOn "^") . splitOn "="

escape = concatMap f where
    f '^' = "\\^{}"
    f x = [x]

main = do
    x <- newIORef 0
    n <- readLn
    forM_ (sequence (take n (repeat "01^="))) $ \s -> 
        when (isOk s) $ do
            putStrLn ("\\texttt{" ++ escape s ++ "},")
            vx <- readIORef x
            writeIORef x (vx + 1)
    vx <- readIORef x
    print vx

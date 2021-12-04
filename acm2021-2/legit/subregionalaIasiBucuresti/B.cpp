for(int append = 0; append < (1<<10); append++) {
    long long freq = ansR[append] - ansL[append];
    for(int msk = 0; msk < (1<<10); msk++)
        for(int cnt = 0; cnt <= k; cnt++) {
            long long comb = 1;
            for(long long cntAppend = 0; cntAppend < min(freq, k - cntAppend); cntAppend++) {
                modes[1-use][cnt+cntAppend][(msk&append)] = (modes[1-use][cnt+cntAppend][(msk&append)] + 1LL*modes[use][cnt][msk]*comb)%mod;
                comb = (1LL*comb*((freq-cntAppend)%mod))%mod;
                comb = (1LL*comb*inv[cntAppend+1])%mod;
            }
        }
    use = 1 - use;
}

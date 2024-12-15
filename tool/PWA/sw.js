const cacheName = "QtThemeCache";
const cacheFileList = [
    "/QtTheme/",
    "/QtTheme/index.html",
    "/QtTheme/QtTheme.html",
    "/QtTheme/qtloader.js",
    "/QtTheme/QtTheme.js", 
    "/QtTheme/QtTheme.wasm", 
    "/QtTheme/icon.svg",
    "/QtTheme/qtlogo.svg",
    "/QtTheme/registerSW.js"
];


self.addEventListener("install", (event) => {
    event.waitUntil(async () => {
        const cache = await caches.open(cacheName);
        return cache.addAll(cacheFileList);
    });
});


self.addEventListener('fetch', (event) => {
    const callback = async () => {
        const url = new URL(event.request.url);
        if (cacheFileList.includes(url.pathname)) {
            const cachedResponse = await caches.match(event.request);
            if (cachedResponse) {
                // 更新缓存
                fetch(event.request).then((networkResponse) => {
                    caches.open(cacheName).then((cache) => {
                        cache.put(event.request, networkResponse.clone());
                    })
                });

                return cachedResponse;
            } else {
                const networkResponse = await fetch(event.request);
                const cache = await caches.open(cacheName);
                cache.put(event.request, networkResponse.clone());
                return networkResponse;
            }
        } else {
            const networkResponse = await fetch(event.request);
            return networkResponse;
        }
    }

    event.respondWith(callback());
});
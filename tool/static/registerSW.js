if ('serviceWorker' in navigator) {
    window.addEventListener('load', () => {
        navigator.serviceWorker.register('/QtTheme/sw.js', { scope: '/QtTheme/' });
    })
}
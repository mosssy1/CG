document.addEventListener("DOMContentLoaded", function () {

    const fileInput = document.getElementById("fileInput");
    const image = document.getElementById("image");

    fileInput.addEventListener("change", function (event) {
        const file = event.target.files[0];
        if (file) {
            loadImage(file);
        }
    });
// переназвать getImage
// поправить драг, сделать так, чтобы мышка не прилипала при переключении
    function loadImage(file) {
        const reader = new FileReader();

        reader.onload = function (e) {
            var imageForProperties = new Image();
            imageForProperties.src = reader.result; 
            imageForProperties.onload = function(){
                image.style.width = this.width + 'px';
                image.style.height = this.height + 'px';
            }
            image.style.backgroundImage = `url('${e.target.result}')`;
        };

        reader.readAsDataURL(file);
    }

    image.addEventListener("mousedown", startDrag);

    let offsetX, offsetY, dragging = false;

    function startDrag(e) {
        dragging = true;
        offsetX = e.clientX - image.offsetLeft;
        offsetY = e.clientY - image.offsetTop;
    }

    function endDrag() {
        dragging = false;
    }

    function drag(e) {
        if (dragging) {
            image.style.left = e.clientX - offsetX + 'px';
            image.style.top = e.clientY - offsetY + 'px';
        }
    }

    document.addEventListener("mouseup", endDrag);
    document.addEventListener("mousemove", drag);
});
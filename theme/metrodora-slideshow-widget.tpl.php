<?php

/**
 * @file
 * islandora-matomo-widget.tpl.php
 */
?>
<?php dpm($objects); ?>
<?php if (count($objects)): ?>
    <div class="container">
        <div id="FrontPageCarousel" class="carousel slide" data-ride="carousel">
            <!-- Indicators -->
            <ol class="carousel-indicators">
                <li data-target="#FrontPageCarousel" data-slide-to="0" class="active"></li>
                <li data-target="#FrontPageCarousel" data-slide-to="1"></li>
                <li data-target="#FrontPageCarousel" data-slide-to="2"></li>
                <li data-target="#FrontPageCarousel" data-slide-to="3"></li>
                <li data-target="#FrontPageCarousel" data-slide-to="4"></li>
                <li data-target="#FrontPageCarousel" data-slide-to="5"></li>
                <li data-target="#FrontPageCarousel" data-slide-to="6"></li>
                <li data-target="#FrontPageCarousel" data-slide-to="7"></li>
                <li data-target="#FrontPageCarousel" data-slide-to="8"></li>
                <li data-target="#FrontPageCarousel" data-slide-to="9"></li>
            </ol>
            <!-- Wrapper for slides -->
            <div class="carousel-inner">
              <?php foreach ($objects as $object): ?>

                <div class="item active">
                    <img src="<?php echo $object['iiif_url']; ?>" alt="<?php echo $object['object_label']; ?>" style="width:100%;">
                    <div class="carousel-caption">
                        <h3>NPL</h3>
                        <p><?php echo $object['object_label']; ?></p>
                    </div>
                </div>
            <?php endforeach;?>
            </div>

            <!-- Left and right controls -->
            <a class="left carousel-control" href="#FrontPageCarousel" data-slide="prev">
                <span class="glyphicon glyphicon-chevron-left"></span>
                <span class="sr-only">Previous</span>
            </a>
            <a class="right carousel-control" href="#FrontPageCarousel" data-slide="next">
                <span class="glyphicon glyphicon-chevron-right"></span>
                <span class="sr-only">Next</span>
            </a>
        </div>
    </div>
<?php endif;?>

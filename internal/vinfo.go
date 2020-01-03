package internal

import (
	"github.com/giorgisio/goav/avformat"
	"log"
)

type VideoInfoRunnable struct {
}

func (v VideoInfoRunnable) Run() {
	f := "/Users/kakaxi/Desktop/huojianshaonv101.MP4"

	// Register all formats and codecs
	avformat.AvRegisterAll()

	ctx := avformat.AvformatAllocContext()

	// Open video file
	if avformat.AvformatOpenInput(&ctx, f, nil, nil) != 0 {
		log.Println("Error: Couldn't open file.")
		return
	}

	// Retrieve stream information
	if ctx.AvformatFindStreamInfo(nil) < 0 {
		log.Println("Error: Couldn't find stream information.")

		// Close input file and free context
		ctx.AvformatCloseInput()
		return
	}

	ctx.AvFormatGetMetadataHeaderPadding()
}
